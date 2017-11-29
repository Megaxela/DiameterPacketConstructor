# Diameter Packet Constructor
It's pure C++11 library for constructing and parsing binary Diameter packets.
This library uses [ByteArray](https://github.com/Megaxela/ByteArray) submodule.

## Build
0. Clone repo: `git clone https://github.com/Megaxela/DiameterPacketConstructor`
0. Go into repo: `cd DiameterPacketConstructor`
0. Init and update submodule: `git submodule init && git submodule update`
0. Create build folder: `mkdir build`
0. Go into build folder: `cd build`
0. Generate build file for your compiler: `cmake ..` (or `cmake -DDIAMETER_BUILD_TESTS .. ` if you want to build tests)
0. Build library: `cmake --build .`

## Example

**Constructing sample DPR packet**
```cpp
auto packet = Diameter::Packet()
        .setHeader(
            Diameter::Packet::Header()
                // It's 1 by default. But for explicity i redefined it. 
                .setVersion(1)
                // Setting that it's request 
                .setCommandFlags(
                    Diameter::Packet::Header::Flags()
                        .setFlag(Diameter::Packet::Header::Flags::Bits::Request, true)
                )
                .setCommandCode(282)
                .setApplicationId(0)
                .setHBHIdentifier(0x7ddf9367)
                .setETEIdentifier(0xc15ecb12)
        )
        .addAVP( // Origin-Host AVP
            Diameter::AVP()
                .setHeader(
                    Diameter::AVP::Header()
                        .setAVPCode(264)
                        .setFlags(
                            Diameter::AVP::Header::Flags()
                                .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                        )
                )
                .setData(
                    Diameter::AVP::Data()
                        .setOctetString(
                            ByteArray::fromASCII("originHostname")
                        )
                )
                // Updating AVP length field, according to header and data value.
                .updateLength()
        )
        .addAVP( // Disconnection-Cause
            Diameter::AVP()
                .setHeader(
                    Diameter::AVP::Header()
                        .setAVPCode(273)
                        .setFlags(
                            Diameter::AVP::Header::Flags()
                                .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                        )
                )
                .setData(
                    Diameter::AVP::Data()
                        .setUnsigned32(0) // REBOOT
                )
                // Updating AVP length field, according to header and data value.
                .updateLength()
        )
        .addAVP( // Origin-Realm
            Diameter::AVP()
                .setHeader(
                    Diameter::AVP::Header()
                        .setAVPCode(296)
                        .setFlags(
                            Diameter::AVP::Header::Flags()
                                .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                        )
                )
                .setData(
                    Diameter::AVP::Data()
                        .setOctetString(
                            ByteArray::fromASCII("originRealm")
                        )
                )
                // Updating AVP length field, according to header and data value.
                .updateLength()
        )
        // Updating Message length field, accordign to added AVPs
        .updateLength()
        // Serializing Packet to ByteArray.
        .deploy();
```

**Parsing binary packet**
```cpp
ByteArray binaryPacket; // Some binary

Diameter::Packet packet;

try
{
    packet = Diameter::Packet(binaryPacket);
}
catch (std::invalid_argument& e)
{
    std::cerr << "Parsing error: " << e.what() << std::endl;
}
```

## LICENSE

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

Library is licensed under the [MIT License](https://opensource.org/licenses/MIT) 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.