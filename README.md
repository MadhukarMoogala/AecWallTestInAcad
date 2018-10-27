# AecWallTestInAcad
This is a test app using OMF 2019 SDK, objective is find out if we can use OMF SDK in pure AutoCAD.
# Steps to Build
- `git clone https://github.com/MadhukarMoogala/AecWallTestInAcad.git`
- cd AecWallTestInAcad
- edit AecWallTestInAcad/AecWallTest.vcxproj to suit your ObjectARX 2019\OMF 2019 SDK in following places
  - [Add-Your-SDK-PATH-Here](https://github.com/MadhukarMoogala/AecWallTestInAcad/blob/2a4fec193f0c59acf0d671a693891f6bdc35b7e3/AecWallTest.vcxproj#L152)
  - [Here](https://github.com/MadhukarMoogala/AecWallTestInAcad/blob/2a4fec193f0c59acf0d671a693891f6bdc35b7e3/AecWallTest.vcxproj#L153)
  - [And Here](https://github.com/MadhukarMoogala/AecWallTestInAcad/blob/2a4fec193f0c59acf0d671a693891f6bdc35b7e3/AecWallTest.vcxproj#L163)
  - [Yes! Here too](https://github.com/MadhukarMoogala/AecWallTestInAcad/blob/2a4fec193f0c59acf0d671a693891f6bdc35b7e3/AecWallTest.vcxproj#L165)
- Build Solution
- Launch AutoCAD, `appload ".\AecWallTest\x64\AecWallTest.arx"`