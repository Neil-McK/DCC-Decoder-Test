# DCC-Decoder-Test

This project was produced to allow testing of DCC Decoders to determine the range of pulse lengths that
the decoder accepts.

Nominal DCC pulse lengths (half-pulse-lengths, in fact) are 58us for a '1' bit and 100us for a '0' bit.
DCC++EX uses 58us and 116us, to simplify the pulse generation code.  Decoders are, according to the NMRA
and RCN specs, required, as a minimum, to accept 58us +/- 6us as valid '1' bits, and anything between 90us and 10,000us for
valid '0' bits.  I wanted to see exactly how well commercial decoders adhered to this and how much additional 
tolerance they might allow.

The program is a modification of the DCC++ Classic CommandStation, since this is not constrained to generating 
'0' pulses that are twice the length of the '1' pulse, as DCC++EX is.  All that remains is the code for generating 
DCC signals in response to commands sent over the serial line.  All that has been added is a command that allows the 
pulse lengths for '1' and '0' bits to be set on-the-fly.  Only the Arduino Mega is supported.

The Classic programming mode is unfortunately not reliable enough for testing the pulse width; consequently, it is recommended
that tests are performed by using the function commands and throttle commands.  Change the DCC pulse length, and then modify the
speed of the engine or trigger a sound or LED function, and see whether the change is effective at the current pulse length.  

The new command is in the form `<l 1|0 n>` where the first character is lower-case 'L', and `n` is an integer.
So to set the nominal pulse lengths of 58us and 100us, you would send `<l 1 58><l 0 100>`.  
To increase the length of the '1' pulse by 2us, send `<l 1 60>`.

Example commands:
```
  <l 1 58><l 0 100>          Set 'nominal' pulse lengths 58/100us
  <t 1 3 50 1>               Set throttle to 50 for loco 3
  <l 1 40>                   Set '1' bit to 40us
  <t 1 3 0 1>                Try to stop loco
```

