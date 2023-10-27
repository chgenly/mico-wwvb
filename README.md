# &mu;WWVB: a tiny wwvb station

&mu;WWVB is a low power 60 khz [WWVB] transmitter used
to automatically set the time on radio synchronized clocks and wristwatches where the regular [WWVB] signal isn’t available. The system acquires
the correct time via GPS.

## Anish Athalye's project

I started with this 2016 github project.

-  His github project https://github.com/anishathalye/micro-wwvb.git 
-  His [blog post][micro-wwvb-post].

Thanks to Anish for making it available. 

## My situation

I live in Forest Grove, Oregon.  The opposite coast where Anish had his problem. I'm not able to reliably receive [WWVB], and especially not inside my house.  

I started searching for information on WWVB signals and ran 
across Anish's project.  It was perfect for what I wanted to do.

Anish seemed to have access to a lot of equipment for building the physical part of the stand.    I don't have access so I'm just going to be using a simple plastic box as a case.

I haven't made my own PC board since 1974.  A lot of taping was involved and then an etching bath.  I was pleased to discover open source schematic and printed circuit board editors.  I was
also pleased to discover online services which would accept [gerber files](https://en.wikipedia.org/wiki/Gerber_format) and mail you a finished PCB.

## KiCad

For my open source schematic/PCB editor I chose [KiCad].  I had never used it before.  So there was a bit of a learning curve.

### autorouting
Install the Freerouting plugin.
1. Open KiCad Project Manager
1. Click on Plugin and Content Manager
1. Fine Freerouting
1. Click on install
1. Click on Apply Pending Changes.
1. You will have to have Java installed for it to work.


## PCB fabrication service

I used [Osh Park](https://oshpark.com) as my fabrication service.  They accept KiCad pcb files directly.  No need to export to gerber files.  The are the cheapest service I could fine.  Interestingly, they just happen to be local to me.

[WWVB]: https://www.nist.gov/pml/time-and-frequency-division/radio-stations/wwvb
[micro-wwvb-post]: https://www.anishathalye.com/2016/12/26/micro-wwvb/

[KiCad]: https://www.kicad.org/
