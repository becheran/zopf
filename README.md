# zopf

Zopf Maschine Esther

An Arduino Nano moves a hair tail (Zopf) back and forth with an MG90S servo, powered by 4x AAA NiMH cells.

## Materials

| Qty | Part | Notes |
| --- | ---- | ----- |
| 1 | Arduino Nano (ATmega328P) | Clone or original |
| 1 | MG90S micro servo (metal gear) | Stall current roughly 0.7-1.2 A |
| 4 | AAA NiMH rechargeable cells (1.2 V) | ~4.8 V total. **Use NiMH only**: 4x alkaline = 6 V, which is too much for the Nano's 5V pin. AA NiMH cells work better (less heat, longer runtime) if they fit |
| 1 | 4x AAA battery holder | |
| 1 | SPDT slide switch (3 pins) | On/off |
| 1 | PTC resettable fuse, 0.5 A hold / 1 A trip | e.g. Bourns MF-R050 or Littelfuse RXEF050. Protects the batteries if the servo is blocked |
| 1 | Electrolytic capacitor 470-1000 uF, >= 10 V | Smooths the servo's current spikes |
| - | Wires, solder, heat shrink | |

## Wiring

Servo sweep on an Arduino Nano, powered by 4x AAA NiMH cells (~4.8 V) connected to the Nano's **5V pin** (not VIN).

![Wiring diagram](docs/wiring.svg)

| Part | Connects to |
| ---- | ----------- |
| Battery + | PTC fuse, then fuse to switch middle pin (COM); switch outer pin to Nano 5V and servo red (other outer pin unused) |
| Battery - | Nano GND, servo brown |
| Servo signal (orange) | Nano D6 |
| Capacitor (470-1000 uF, >=10 V) | + leg (long) to servo red / 5V, - leg (short, stripe) to servo brown / GND, placed right at the servo |

Unplug the battery pack before connecting USB to upload.

## Why the batteries got hot, and how this is prevented

A servo pushes with **full power** whenever it is not yet at its target angle. If the tail is heavy, swings hard, or gets blocked, the MG90S pulls its stall current (around 1 A). The small AAA cells heat up quickly at that current, and so does the servo motor.

Protection, in layers:

1. **Mechanics:** mount the tail close to the servo shaft and keep it light. Make sure it can swing freely over the whole range and never hits anything. This matters most.
2. **PTC fuse (hardware backup):** if the servo stays blocked anyway, the fuse heats up after a few seconds and cuts the current. It resets itself: switch off, wait about a minute, free the tail, switch on.

If the batteries still get warm, make the movement slower (increase `MOVE_MS`), make the range smaller, or switch to AA NiMH cells. If the pack gets hot even **without** the tail mounted, check the wiring for a short circuit and check that the capacitor isn't in backwards.
