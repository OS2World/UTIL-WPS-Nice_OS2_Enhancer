#define INCL_DOSERRORS

#include <os2.h>

#include <stdio.h>
#include <string.h>

#include "USBCalls/USB.h"
#include "USBCalls/USBCalls.h"

struct _GPPortPrivateLibrary
{
  USBHANDLE dh;
  CHAR ucDevDesc[2048];
  struct usb_device_descriptor *pDevDesc;
  struct
  {
    INT config;
    INT interface;
    INT altsetting;
    INT inep, outep, intep;
  }
  usb;
};

struct usb_descriptor_header *GetNextDescriptor (struct usb_descriptor_header *currHead, UCHAR *lastBytePtr)
{
  UCHAR *currBytePtr = NULL;
  UCHAR *nextBytePtr = NULL;

  if (!currHead || !currHead->bLength) return NULL;
  if (!lastBytePtr) return NULL;

  currBytePtr = (UCHAR*) currHead;
  nextBytePtr = currBytePtr + currHead->bLength;

  if (nextBytePtr >= lastBytePtr) return NULL;

  return (struct usb_descriptor_header*) nextBytePtr;
}

INT usb_find_endpoint (CHAR *pData, INT config, INT interface, INT altsetting, INT direction, INT type)
{
 struct usb_device_descriptor *pDevDesc = NULL;
 struct usb_config_descriptor *pCfgDesc = NULL;
 struct usb_interface_descriptor *intrfce = NULL;
 struct usb_endpoint_descriptor *ep = NULL;
 struct usb_descriptor_header *pDescHead = NULL;

 INT i = 0;

 if (!pData) return -1;

 pDevDesc = (struct usb_device_descriptor*) pData;
 pCfgDesc = (struct usb_config_descriptor*) (pData + sizeof (struct usb_device_descriptor));

 for (i = 0; i < pDevDesc->bNumConfigurations; i ++)
 {
   UCHAR *pCurPtr = (UCHAR*) pCfgDesc;
   UCHAR *pEndPtr = pCurPtr + pCfgDesc->wTotalLength;
   pDescHead = (struct usb_descriptor_header*) (pCurPtr + pCfgDesc->bLength);

   if (pCfgDesc->bConfigurationValue == config)
   {
     for (pDescHead = (struct usb_descriptor_header*) (pCurPtr + pCfgDesc->bLength);
          pDescHead != NULL;
          pDescHead = GetNextDescriptor (pDescHead, pEndPtr))
     {
       switch (pDescHead->bDescriptorType)
       {
         case USB_DT_INTERFACE:
         {
           intrfce = (struct usb_interface_descriptor *) pDescHead;
         }
         break;

         case USB_DT_ENDPOINT:
         {
           ep = (struct usb_endpoint_descriptor*) pDescHead;

           if ((intrfce->bInterfaceNumber == interface) &&
               (intrfce->bAlternateSetting == altsetting) &&
               ((ep->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == direction) &&
               ((ep->bmAttributes & USB_ENDPOINT_TYPE_MASK) == type)) return ep->bEndpointAddress;
         }
         break;
       }
     }

     return -1;
   }

   pCfgDesc = (struct usb_config_descriptor*) pEndPtr;
 }

 return -1;
}

INT usb_match_device_by_class (PCHAR pData, INT devclass, INT subclass, INT protocol, INT *configno, INT *interfaceno, INT *altsettingno)
{
 INT i = 0, j = 0;
 struct usb_device_descriptor *pDevDesc = (struct usb_device_descriptor*) pData;
 struct usb_descriptor_header *pDescHead = NULL;
 struct usb_config_descriptor *pCfgDesc = NULL;

 if (pDevDesc->bDeviceClass == devclass &&
     (subclass == -1 || pDevDesc->bDeviceSubClass == subclass) &&
     (protocol == -1 || pDevDesc->bDeviceProtocol == protocol)) return 1;

 pCfgDesc = (struct usb_config_descriptor*) (pData + pDevDesc->bLength);

 for (i = 0; i < pDevDesc->bNumConfigurations; i ++)
 {
   UCHAR *pCurPtr = (UCHAR*) pCfgDesc;
   UCHAR *pEndPtr = pCurPtr + pCfgDesc->wTotalLength;
   pDescHead = (struct usb_descriptor_header *) (pCurPtr + pCfgDesc->bLength);

   for (j = 0, pDescHead = (struct usb_descriptor_header *) (pCurPtr + pCfgDesc->bLength);
        pDescHead != NULL;
        j++, pDescHead = GetNextDescriptor (pDescHead, pEndPtr))
   {
     if (pDescHead->bDescriptorType == USB_DT_INTERFACE)
     {
       struct usb_interface_descriptor *pIfDesc = (struct usb_interface_descriptor *) pDescHead;

       if (pIfDesc->bInterfaceClass == devclass &&
           (subclass == -1 || pIfDesc->bInterfaceSubClass == subclass) &&
           (protocol == -1 || pIfDesc->bInterfaceProtocol == protocol))
       {
          *configno = pCfgDesc->bConfigurationValue;
          *interfaceno = pIfDesc->bInterfaceNumber;
          *altsettingno = pIfDesc->bAlternateSetting;

          return 1;
       }
     }
   }

   pCfgDesc = (struct usb_config_descriptor*) pEndPtr;
 }

 return 0;
}

INT usb_find_device_by_class (struct _GPPortPrivateLibrary *pl, INT devclass, INT subclass, INT protocol)
{
  APIRET rc = NO_ERROR;
  ULONG ulNumDev = 0, ulDev = 0, ulBufLen = 0;

  if (!devclass) return 0;

  rc = UsbQueryNumberDevices (&ulNumDev);

  if (rc == NO_ERROR && ulNumDev)
  {
    for (ulDev = 1; ulDev <= ulNumDev; ulDev ++)
    {
      INT ret = 0, config = 0, interface = 0, altsetting = 0;
      ulBufLen = sizeof (pl->ucDevDesc);
      memset (pl->ucDevDesc, 0, sizeof (pl->ucDevDesc));

      rc = UsbQueryDeviceReport (ulDev, &ulBufLen, (PCHAR) pl->ucDevDesc);

      if (!usb_match_device_by_class (pl->ucDevDesc, devclass, subclass, protocol, &config, &interface, &altsetting)) continue;

      rc = UsbOpen (&(pl->dh), pl->pDevDesc->idVendor, pl->pDevDesc->idProduct, pl->pDevDesc->bcdDevice, USB_OPEN_FIRST_UNUSED);

      if (rc == NO_ERROR && pl->dh != NULLHANDLE)
      {
        printf ("Looking for USB device (class 0x%x, subclass, 0x%x, protocol 0x%x)... found.\n",
                devclass, subclass, protocol);

        pl->usb.config = config;
        pl->usb.interface = interface;
        pl->usb.altsetting = altsetting;

        pl->usb.inep = usb_find_endpoint (pl->ucDevDesc, config, interface, altsetting, USB_ENDPOINT_IN, USB_ENDPOINT_TYPE_BULK);
        pl->usb.outep = usb_find_endpoint (pl->ucDevDesc, config, interface, altsetting, USB_ENDPOINT_OUT, USB_ENDPOINT_TYPE_BULK);
        pl->usb.intep = usb_find_endpoint (pl->ucDevDesc, config, interface, altsetting, USB_ENDPOINT_IN, USB_ENDPOINT_TYPE_INTERRUPT);

        printf ("Detected defaults: config %d, interface %d, altsetting %d, inep %02x, outep %02x, intep %02x\n",
                pl->usb.config, pl->usb.interface, pl->usb.altsetting, pl->usb.inep, pl->usb.outep, pl->usb.intep);

        return 1;
      }
    }
  }

  printf ("Could not find USB device " \
          "(class 0x%x, subclass 0x%x, protocol 0x%x). Make sure this device " \
          "is connected to the computer.\n", devclass, subclass, protocol);

  return 0;
}


void main ()
{
  struct _GPPortPrivateLibrary pl; memset (&pl, 0, sizeof (pl));
  pl.pDevDesc = (struct usb_device_descriptor*) pl.ucDevDesc;

  if (usb_find_device_by_class (&pl, USB_CLASS_HID, 0, 0))
  {
    printf ("Found USB MM keyboard (%04x:%04x)\n",
            pl.pDevDesc->idVendor, pl.pDevDesc->idProduct);

    while (1)
    {
      INT rc = NO_ERROR;
      UCHAR data[64] = "";
      INT read = sizeof (data);
      INT timeout = 10 * 1000;

      rc = UsbIrqRead (pl.dh, pl.usb.intep, pl.usb.interface, (PULONG) &read, data, timeout);

      printf ("UsbIrqRead rc = %04x, read = %d\n",
               rc, read
     );

      if (rc == NO_ERROR)
      {
        INT i;

        for (i = 0; i < read; i++) printf (" %02x", data[i]);
        printf ("\n");

        continue;
      }
      else
      {
        if (rc == ERROR_TIMEOUT)
        {
          printf ("Timeout\n");
        }
        else
        {
          printf ("Unpredicted error\n");
        }

        break;
      }
    }
  }

  UsbClose (pl.dh);

  return;
}
