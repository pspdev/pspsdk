This sample uses the sceChnnlsv module directly to do savegame
decryption.  It currently works only in VSH mode (e.g., via the TIFF
exploit).  It can handle both old and new format saves (SaveParam
structure sizes 0x5c8, 0x5dc, 0x600).  New format saves require a
game-specific encryption key.
