# Victorique


A tool to handle files used in the various versions of the Visual Novel White Album 2, it can currently handle extracting and repacking .pak files.<br>

<img align="left" width="230" src="https://i.imgur.com/F8suY5v.png">

##### How it is done?
Check the [Wiki](https://github.com/raphasanori/Kazusa/wiki) to reverse enginnering documentation.<br>

##### How do I build it?

It can be easily built with a C compiler (with support to C11), premake5, and the sub-module Victorique.<br>

##### Multi-platform?

It's tested only on Windows 10, but can compile even in XP, probably.<br>
But can probably work on other systems with a bit of work!<br>
Also known as, rewrite the encode convertion functions that use the Windows API!<br>
#### Status
Version 1.0a<br>
[![Build Status](https://travis-ci.org/raphasanori/Kazusa.svg?branch=master)](https://travis-ci.org/raphasanori/Kazusa)<hr>
<sub>Kazusa © Copyright  2020 - raphasanori<br>
Kazusa Touma image belongs to Leaf and their creators!<br>This library has no connection with them, the image on the side is just for decoration.</sub>




# Kazusa



.

#### Usage

Usage:

Kazusa.exe [option {e:extract/p:pack}] input output [skip{y:yes/n:no}]

Skip will skip questions about directory creation and stuff.

#### PAK file basic structure

##### Main Header
The first thing on the file is the main header, that contains the file identification, some unknown stuff at the moment and the number of entries.

| MAGIC WORD (4 bytes)  | Must be "KCAP" |
| ------------ | ------------ |
|  UNKNOWN VALUE (8 bytes) | Random eg. 0xFFFFFFFF  |
| NUMBER OF ENTRIES (4bytes)  |  Includes folders and files  |

##### Entries

The main header is followed by the entries, one after another, each one with 44 bytes in size.

| COMPRESSED (4 bytes) | 0x00000000 = Not compressed <br />0x00000001 = Compressed<br /> 0xCCCCCCCC = Folder |
| ------------ | ------------ |
| FILENAME (24 bytes) | Only the current entry file, encoded in Shift_JIS |
| UNKNOWN (8 bytes) |  Random eg. 0xFFFFFFFF |
| OFFSET (4 bytes) |  Relative to the beggining of the file  |
| LENGTH (4 bytes)  | When compressed = Compressed length <br/> When not compressed, original/total length |

##### Data

After all the entries, we have the data (and if compressed a mini header).

###### If compressed

| COMPRESSED LENGTH (4 bytes) | Can be wrong?! <br/> Believe in the main entry one  |
| ------------ | ------------ |
| ORIGINAL LENGTH (4 bytes) | Original length used to decompress the data  |
| DATA | Until the EOF  |

###### If not compressed

Its straight data until the EOF.

#### Compression

The compression algorithm used is a variation of the original LZSS, more info inside lzss.c.

