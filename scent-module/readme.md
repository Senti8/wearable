# Senti8 Wearable Device

This contains the "connectible" version of the Senti8 wearable firmware.
It responds to commands received via software serial. See the
[communications module][1] repo for details about the protocol.

During the [presentation][2], one wristband used this firmware, connected via
two wires to another Arduino running the SimpleComms sketch which itself
could connect to an iOS [companion app][4] via a Bluetooth Smart link.

The hardcoded "demo" firmware is available at the [alternate repo][3].

[1]: ../comms-module/readme.md
[2]: https://plus.google.com/113329514392137754139/posts/JGAhFkpgpnq
[3]: https://github.com/Senti8/neopixel_cuff
[4]: https://github.com/Senti8/mobile

