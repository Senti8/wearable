# Senti8 Communications Module

This is the communications module for the Senti8 wearable wristband
created as part of the [2014 NASA Space Apps Challenge][1], solving the
[Space Wearables: Fashion Designer to Astronauts challenge][2].

It exists to bridge the Bluetooth Smart (BLE) link to a wired serial
connection on the wristband. Eventually, the wearable would
directly incorporate BLE hardware and this firmware would be merged
into the wearable firmware. During the hackathon, it was necessary to
separate these components due to hardware availablity limitations and
separation of roles amongst teammates.

## Building
These sketches were written using the Arduino IDE v1.5+ and targeted the
Arduino Leonardo hardware. The SimpleComms sketch is used for the
prototype demo; the other sketches were simple proof-of-concepts.

## Communication Protocol
There are several common approaches but fixed message length is the most straightforward.
We will use messages that are exactly three bytes long:

| Byte 0 | Byte 1 | Byte 2 |
| ------ | ------ | ------ |
| commandID | payload byte 0 | payload byte 1 |

<table border="1">
<tr>
<th>Command</th>
<th>CommandID</th>
<th>Payload byte 0</th>
<th>Payload byte 1</th>
<th>Notes</th>
</tr>
<tr>
<td>Emit scent</td>
<td>`0x10`</td>
<td>
    0x0 - (Reserved)
    0x1 - Soil
    0x2 - Home
    0x3 - Food
    0x4 - Nature
    0x5 - Space
    0x6 - Fire
</td>
<td>`0x0 (not used)`</td>
<td>Device should “play” the selected scent.</td>
</tr>
<tr>
<td>Scent selected (not used)</td>
<td>`0x1a`</td>
<td>
    0x0 - (Reserved)
    0x1 - Soil
    0x2 - Home
    0x3 - Food
    0x4 - Nature
    0x5 - Space
    0x6 - Fire
</td>
<td>`0x0 (not used)`</td>
<td>Button was pressed on the device. (TBD)</td>
</tr>
</table>


## Bluetooth Low Energy shields
We are using a BLE Arduino Shield to provide simple connectivity,
the [RedBear BLE Shield](http://redbearlab.com/bleshield/).
