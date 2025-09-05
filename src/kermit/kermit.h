#ifndef __KERMIT_H__
#define __KERMIT_H__

#include <pspsdk.h>

#define KERMIT_MAX_ARGC     (14)

/* kermit KERMIT_MODE_PERIPHERAL commands */
#define KERMIT_CMD_RTC_GET_CURRENT_TICK     (0x0)
#define KERMIT_CMD_ID_STORAGE_LOOKUP        (0x1)
#define KERMIT_CMD_POWER_FREQUENCY          (0x2)
#define KERMIT_CMD_AUDIO_ROUTING            (0x3)
#define KERMIT_CMD_GET_CAMERA_DIRECTION     (0x5)
#define KERMIT_CMD_GET_IDPSC_ENABLE         (0x6)
#define KERMIT_CMD_DISABLE_MULTITASKING     (0x7)
#define KERMIT_CMD_ERROR_EXIT               (0x8)
#define KERMIT_CMD_ERROR_EXIT_2             (0x422)
#define KERMIT_CMD_ENABLE_MULTITASKING      (0x9)
#define KERMIT_CMD_RESUME_DEVICE            (0xA)
#define KERMIT_CMD_REQUEST_SUSPEND          (0xB)
#define KERMIT_CMD_IS_FIRST_BOOT            (0xC)
#define KERMIT_CMD_GET_PREFIX_SSID          (0xD)
#define KERMIT_CMD_SET_PS_BUTTON_STATE      (0x10)

/* kermit KERMIT_MODE_MSFS commands */
#define KERMIT_CMD_INIT_MS              (0x0)
#define KERMIT_CMD_EXIT_MS              (0x1)
#define KERMIT_CMD_OPEN_MS              (0x2)
#define KERMIT_CMD_CLOSE_MS             (0x3)
#define KERMIT_CMD_READ_MS              (0x4)
#define KERMIT_CMD_WRITE_MS             (0x5)
#define KERMIT_CMD_SEEK_MS              (0x6)
#define KERMIT_CMD_IOCTL_MS             (0x7)
#define KERMIT_CMD_REMOVE_MS            (0x8)
#define KERMIT_CMD_MKDIR_MS             (0x9)
#define KERMIT_CMD_RMDIR_MS             (0xA)
#define KERMIT_CMD_DOPEN_MS             (0xB)
#define KERMIT_CMD_DCLOSE_MS            (0xC)
#define KERMIT_CMD_DREAD_MS             (0xD)
#define KERMIT_CMD_GETSTAT_MS           (0xE)
#define KERMIT_CMD_CHSTAT_MS            (0xF)
#define KERMIT_CMD_RENAME_MS            (0x10)
#define KERMIT_CMD_CHDIR_MS             (0x11)
#define KERMIT_CMD_DEVCTL               (0x14)

/* kermit KERMIT_MODE_AUDIO commands */
#define KERMIT_CMD_INIT_AUDIO_IN        0x0
#define KERMIT_CMD_OUTPUT_1             0x1
#define KERMIT_CMD_OUTPUT_2             0x2
#define KERMIT_CMD_SUSPEND_AUDIO        0x3
#define KERMIT_CMD_RESUME               0x4

/* kermit KERMIT_MODE_ME commands */
#define KERMIT_CMD_UNK0                     0x0
#define KERMIT_CMD_SETAVC_TIMESTAMPINTERNAL 0x1
#define KERMIT_CMD_BOOT_START               0x2

/* kermit KERMIT_MODE_LOWIO commands */
#define KERMIT_CMD_UNK9     0x9
#define KERMIT_CMD_UNKA     0xA
#define KERMIT_CMD_UNKB     0xB
#define KERMIT_CMD_UNKC     0xC

/* kermit KERMIT_MODE_WLAN commands */
#define KERMIT_CMD_INIT                         0x0
#define KERMIT_CMD_GET_SWITCH_INTERNAL_STATE    0x2
#define KERMIT_CMD_GET_ETHER_ADDR               0x3
#define KERMIT_CMD_ADHOC_CTL_INIT               0x6
#define KERMIT_CMD_ADHOC_CTL_TERM               0x7
#define KERMIT_CMD_ADHOC_SCAN                   0x8
#define KERMIT_CMD_ADHOC_JOIN                   0x9
#define KERMIT_CMD_ADHOC_CREATE                 0xA
#define KERMIT_CMD_ADHOC_LEAVE                  0xB
#define KERMIT_CMD_ADHOC_TX_DATA                0xC
#define KERMIT_CMD_ADHOC_RX_DATA                0xD
#define KERMIT_CMD_INET_INIT                    0xE
#define KERMIT_CMD_INET_START                   0xF
#define KERMIT_CMD_INET_TERM                    0x10
#define KERMIT_CMD_INET_SOCKET                  0x11
#define KERMIT_CMD_INET_CLOSE                   0x12
#define KERMIT_CMD_INET_BIND                    0x13
#define KERMIT_CMD_INET_LISTEN                  0x14
#define KERMIT_CMD_INET_CONNECT                 0x15
#define KERMIT_CMD_INET_SHUTDOWN                0x16
#define KERMIT_CMD_INET_POLL                    0x17
#define KERMIT_CMD_INET_ACCEPT                  0x18
#define KERMIT_CMD_INET_GET_PEER_NAME           0x19
#define KERMIT_CMD_INET_GET_SOCK_NAME           0x1A
#define KERMIT_CMD_INET_GET_OPT                 0x1B
#define KERMIT_CMD_INET_SET_OPT                 0x1C
#define KERMIT_CMD_INET_RECV_FROM               0x1D
#define KERMIT_CMD_INET_SENDTO_INTERNAL         0x1E
#define KERMIT_CMD_INET_SOIOCTL                 0x1F
#define KERMIT_CMD_SUSPEND_WLAN                 0x20
#define KERMIT_CMD_SET_WOL_PARAM                0x22
#define KERMIT_CMD_GET_WOL_INFO                 0x23
#define KERMIT_CMD_SET_HOST_DISCOVER            0x24

/* kermit KERMIT_MODE_UTILITY commands */
#define KERMIT_CMD_OSK_START    (0x0)
#define KERMIT_CMD_OSK_SHUTDOWN (0x1)
#define KERMIT_CMD_OSK_UPDATE   (0x3)

/* kermit KERMIT_MODE_USB commands */
#define KERMIT_CMD_INIT         0x0
#define KERMIT_CMD_ACTIVATE     0x15
#define KERMIT_CMD_DEACTIVATE   0x16
#define KERMIT_CMD_SET_OP       0x19
#define KERMIT_CMD_SET_OP_BIS   0x1A
#define KERMIT_CMD_UNK1B        0x1B


/* KERMIT_PACKET address macros */
#define KERNEL(x)   ((x & 0x80000000)? 1:0)
#define KERMIT_PACKET(x)    (x | (2-KERNEL(x))*0x20000000)
#define ALIGN_64(x) ((x) & -64)
#define KERMIT_CALLBACK_DISABLE 0

enum KermitModes {
    KERMIT_MODE_NONE,
    KERMIT_MODE_UNK_1,
    KERMIT_MODE_UNK_2,
    KERMIT_MODE_MSFS,
    KERMIT_MODE_FLASHFS,
    KERMIT_MODE_AUDIOOUT,
    KERMIT_MODE_ME,
    KERMIT_MODE_LOWIO,
    KERMIT_MODE_POCS_USBPSPCM,
    KERMIT_MODE_PERIPHERAL,
    KERMIT_MODE_WLAN,
    KERMIT_MODE_AUDIOIN,
    KERMIT_MODE_USB,
    KERMIT_MODE_UTILITY,
    KERMIT_MODE_EXTRA_1,
    KERMIT_MODE_EXTRA_2,
};

enum KermitVirtualInterrupts {
    KERMIT_VIRTUAL_INTR_NONE,
    KERMIT_VIRTUAL_INTR_AUDIO_CH1,
    KERMIT_VIRTUAL_INTR_AUDIO_CH2,
    KERMIT_VIRTUAL_INTR_AUDIO_CH3,
    KERMIT_VIRTUAL_INTR_ME_DMA_CH1,
    KERMIT_VIRTUAL_INTR_ME_DMA_CH2,
    KERMIT_VIRTUAL_INTR_ME_DMA_CH3,
    KERMIT_VIRTUAL_INTR_WLAN_CH1,
    KERMIT_VIRTUAL_INTR_WLAN_CH2,
    KERMIT_VIRTUAL_INTR_IMPOSE_CH1,
    KERMIT_VIRTUAL_INTR_POWER_CH1,
    KERMIT_VIRTUAL_INTR_UNKNOWN_CH1,    // <- used after settings
    KERMIT_VIRTUAL_INTR_USBGPS_CH1,
    KERMIT_VIRTUAL_INTR_USBPSPCM_CH1,
};

enum KermitArgumentModes {
  KERMIT_INPUT_MODE = 0x1,
  KERMIT_OUTPUT_MODE = 0x2,
};

typedef struct {
    uint32_t cmd; //0x0
    SceUID sema_id; //0x4
    uint64_t *response; //0x8
    uint32_t padding; //0xC
    uint64_t args[14]; // 0x10
} SceKermitRequest; //0x80

// 0xBFC00800
typedef struct {
    uint32_t cmd; //0x00
    SceKermitRequest *request; //0x04
} SceKermitCommand; //0x8

// 0xBFC00840
typedef struct {
    uint64_t result; //0x0
    SceUID sema_id; //0x8
    int32_t unk_C; //0xC
    uint64_t *response; //0x10
    uint64_t unk_1C; //0x1C
} SceKermitResponse; //0x24 or 0x30????

// 0xBFC008C0
typedef struct {
    int32_t unk_0; //0x0
    int32_t unk_4; //0x4
} SceKermitInterrupt; //0x8

typedef struct KermitPacket_
{
    u32 cmd;            //0x0
    SceUID sema;        //0x4
    struct KermitPacket_ *self; //0x8
    u32 unk_C;          //0xC
} KermitPacket;


/*
    Issue a command to kermit.
    
    packet:             a kermit packet. Header followed by 64 bit words (LE) as arguements.
    cmd_mode:           a valid command mode type.
    cmd:                a valid command subtype of cmd_mode.
    argc:               the number of 64 bit arguements following the header. Max 13 arguements.
    allow_callback:     set non-zero to use callback permitting semaphore wait.
    resp:               64 bit word returned by the kermit call.
    
    returns 0 on success, else < 0 on error.
*/
int sceKermit_driver_4F75AA05(KermitPacket *packet, u32 cmd_mode, u32 cmd, u32 argc, u32 allow_callback, u64 *resp);

/*
    Apply IO to kermit packet.
    
    packet:             a kermit packet. Header followed by 64 bit words (LE) as arguements.
    argc:               the number of arguements in the packet. Max 13 arguements.
    buffer:             the input buffer containing the data to be sent or the output buffer to store data.
    buffer_size:        the size of the input data, else the size of the output buffer.
    io_mode:            KERMIT_INPUT_MODE for data input. KERMIT_OUTPUT_MODE for expecting output data.
*/
void sceKermitMemorySetArgument(KermitPacket *packet, u32 argc, u8 *buffer, u32 buffer_size, u32 io_mode);

/*
    Send data to vita host.
    
    data:               pointer to the data to be sent to host.
    len:                the size of the data to be sent.
*/
void sceKermitMemory_driver_80E1240A(u8 *data, u32 len);

/*
    Recieve data from vita host.
    
    data:               pointer to buffer to store output data.
    len:                the size of the expected output data.
*/
void sceKermitMemory_driver_90B662D0(u8 *data, u32 data_size);


/*
  Register handler for a kermit virtual interrupt.

  interrupt:             ID of the virtual interrupt.
  handler:               function pointer.

  returns 0 on success, else < 0 on error.
*/
int sceKermitRegisterVirtualIntrHandler(u32 interrupt, void* handler);

/*
  Send a request to kermit.

  request:                pointer to SceKermitRequest data structure.
  mode:                   ID of the request mode (see enum KermitModes).
  cmd:                    request command ID.
  argc:                   unknown, pass 0.
  callback:               callback mode, pass KERMIT_CALLBACK_DISABLE (0).
  response:               pointer to return value.

  returns 0 on success, else < 0 on error.
*/
int sceKermitSendRequest(SceKermitRequest* request, u32 mode, u32 cmd, int argc, u32 callback, u64* response);

#endif /* __KERMIT_H__ */
