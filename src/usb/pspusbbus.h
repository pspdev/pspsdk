/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspusbbus.h - Prototypes for the sceUsbBus_driver library
 *
 * Copyright (c) 2006 James F 
 *
 * $Id: pspusbbus.h 2219 2007-04-18 19:08:48Z chip $
 */
#ifndef __PSPUSBBUS_H__
#define __PSPUSBBUS_H__

#ifdef __cplusplus
extern "C" {
#endif

/** USB driver interface */
struct UsbInterface
{
	/** Expectant interface (0 or -1) */
	int expect_interface;
	/** Unknown */
	int unk8;
	/** Number of interfaces */
	int num_interface;
};

/** USB driver endpoint */
struct UsbEndpoint
{
	/** Endpoint number (must be filled in sequentially) */
	int endpnum; 
	/** Filled in by the bus driver */
	int unk2; 
	/** Filled in by the bus driver */
	int unk3;
};

/** USB string descriptor */
struct StringDescriptor
{
	unsigned char bLength;
	unsigned char bDescriptorType;
	short bString[32];
} __attribute__((packed));

/** USB device descriptor */
struct DeviceDescriptor
{
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned short bcdUSB;
	unsigned char bDeviceClass;
	unsigned char bDeviceSubClass;
	unsigned char bDeviceProtocol;
	unsigned char bMaxPacketSize;
	unsigned short idVendor;
	unsigned short idProduct;
	unsigned short bcdDevice;
	unsigned char iManufacturer;
	unsigned char iProduct;
	unsigned char iSerialNumber;
	unsigned char bNumConfigurations;
} __attribute__((packed));

/** USB configuration descriptor */
struct ConfigDescriptor
{
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned short wTotalLength;
	unsigned char bNumInterfaces;
	unsigned char bConfigurationValue;
	unsigned char iConfiguration;
	unsigned char bmAttributes; 
	unsigned char bMaxPower; 
} __attribute__((packed));

/** USB Interface descriptor */
struct InterfaceDescriptor
{
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned char bInterfaceNumber;
	unsigned char bAlternateSetting;
	unsigned char bNumEndpoints;
	unsigned char bInterfaceClass;
	unsigned char bInterfaceSubClass;
	unsigned char bInterfaceProtocol;
	unsigned char iInterface;
} __attribute__((packed));

/** USB endpoint descriptor */
struct EndpointDescriptor
{
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned char bEndpointAddress;
	unsigned char bmAttributes;
	unsigned short wMaxPacketSize; 
	unsigned char bInterval;
} __attribute__((packed));

/** USB driver interfaces structure */
struct UsbInterfaces
{
	/** Pointers to the individual interface descriptors */
	struct InterfaceDescriptor *infp[2];
	/** Number of interface descriptors */
	unsigned int num;
};

/** USB driver configuration */
struct UsbConfiguration
{
	/** Pointer to the configuration descriptors */
	struct ConfigDescriptor *confp;
	/** USB driver interfaces pointer */
	struct UsbInterfaces *infs;
	/** Pointer to the first interface descriptor */
	struct InterfaceDescriptor *infp;
	/** Pointer to the first endpoint descriptor (each should be 16byte aligned) */
	struct EndpointDescriptor *endp;
};

/** Padded data structure, padding is required otherwise the USB hardware crashes */
struct UsbData
{
	unsigned char devdesc[20];

	struct Config
	{
		void *pconfdesc;
		void *pinterfaces;
		void *pinterdesc;
		void *pendp;
	} config;
	
	struct ConfDesc
	{
		unsigned char desc[12];
		void *pinterfaces;
	} confdesc;

	unsigned char pad1[8];
	struct Interfaces
	{
		void *pinterdesc[2];
		unsigned int intcount;
	} interfaces;

	struct InterDesc
	{
		unsigned char desc[12];
		void *pendp;
		unsigned char pad[32];
	} interdesc;

	struct Endp
	{
		unsigned char desc[16];
	} endp[4];
} __attribute__((packed));

/** USB EP0 Device Request */
struct DeviceRequest
{
	unsigned char bmRequestType;
	unsigned char bRequest;
	unsigned short wValue;
	unsigned short wIndex;
	unsigned short wLength;
} __attribute__((packed));

/** USB driver structure used by ::sceUsbbdRegisterDriver and ::sceUsbbdUnregisterDriver */
struct UsbDriver
{
	/** Name of the USB driver */
	const char *name; 
	/** Number of endpoints in this driver (including default control) */
	int endpoints;
	/** List of endpoint structures (used when calling other functions) */
	struct UsbEndpoint *endp; 
	/** Interface list */
	struct UsbInterface *intp;	  
	/** Pointer to hi-speed device descriptor */
	void *devp_hi;  
	/** Pointer to hi-speed device configuration */
	void *confp_hi;	
	/** Pointer to full-speed device descriptor */
	void *devp;     
	/** Pointer to full-speed device configuration */
	void *confp;    
	/** Default String descriptor */
	struct StringDescriptor *str; 
	/** Received a control request arg0 is endpoint, arg1 is possibly data arg2 is data buffer */
	int (*recvctl)(int arg1, int arg2, struct DeviceRequest *req);
	/** Unknown */
	int (*func28)(int arg1, int arg2, int arg3);  
	/** Configuration set (attach) function */
	int (*attach)(int speed, void *arg2, void *arg3); 
	/** Configuration unset (detach) function */
	int (*detach)(int arg1, int arg2, int arg3);
	/** Unknown set to 0 */
	int unk34;
	/** Function called when the driver is started */
	int (*start_func)(int size, void *args);
	/** Function called when the driver is stopped */
	int (*stop_func)(int size, void *args);  
	/** Link to next USB driver in the chain, set to NULL */
	struct UsbDriver *link; 
};

/** USB device request, used by ::sceUsbbdReqSend and ::sceUsbbdReqRecv. */
struct UsbdDeviceReq
{
	/** Pointer to the endpoint to queue request on */
	struct UsbEndpoint *endp; 
	/** Pointer to the data buffer to use in the request */
	void *data;
	/** Size of the data buffer (send == size of data, recv == size of max receive) */
	int  size; 
	/** Unknown */
	int  unkc; 
	/** Pointer to the function to call on completion */
	void *func;
	/** Resultant size (send == size of data sent, recv == size of data received) */
	int  recvsize;
	/** Return code of the request, 0 == success, -3 == cancelled */
	int  retcode; 
	/** Unknown */
	int  unk1c;
	/** A user specified pointer for the device request */
	void *arg;
	/** Link pointer to next request used by the driver, set it to NULL */
	void *link;
};

/**
 * Register a USB driver.
 *
 * @param drv - Pointer to a filled out USB driver
 *
 * @return 0 on success, < 0 on error
 */
int sceUsbbdRegister(struct UsbDriver *drv);

/**
 * Unregister a USB driver
 *
 * @param drv - Pointer to a filled out USB driver
 *
 * @return 0 on success, < 0 on error
 */
int sceUsbbdUnregister(struct UsbDriver *drv);

/**
 * Clear the FIFO on an endpoint
 *
 * @param endp - The endpoint to clear
 *
 * @return 0 on success, < 0 on error
 */
int sceUsbbdClearFIFO(struct UsbEndpoint *endp);

/**
 * Cancel any pending requests on an endpoint.
 *
 * @param endp - The endpoint to cancel
 *
 * @return 0 on success, < 0 on error
 */
int sceUsbbdReqCancelAll(struct UsbEndpoint *endp);

/**
 * Stall an endpoint
 *
 * @param endp - The endpoint to stall
 *
 * @return 0 on success, < 0 on error
 */
int sceUsbbdStall(struct UsbEndpoint *endp);

/**
 * Queue a send request (IN from host pov)
 *
 * @param req - Pointer to a filled out UsbdDeviceReq structure.
 *
 * @return 0 on success, < 0 on error
 */
int sceUsbbdReqSend(struct UsbdDeviceReq *req);

/**
 * Queue a receive request (OUT from host pov)
 *
 * @param req - Pointer to a filled out UsbdDeviceReq structure
 *
 * @return 0 on success, < 0 on error
 */
int sceUsbbdReqRecv(struct UsbdDeviceReq *req);

#ifdef __cplusplus
}
#endif

#endif
