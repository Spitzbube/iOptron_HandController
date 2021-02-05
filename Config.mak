################################################################################
################################################################################
##
## Config.mak -- user specific development environment settings
##
## Copy this file into Config.mak.<username> to protect your private settings
## from being overwritten the next time you get an update.
## The make environment will first check for file "Config.mak.<username>",
## it will use the file "Config.mak" only if the user specific configuration
## file does not exist. <username> should be the string reported by
## "echo %USERNAME%" if you are using the standard windows shell, Cygwin
## users should call "echo $USERNAME" instead.
##
################################################################################
################################################################################

  TARGET   ?= arm-realview

  SDKHOME-arm-gcc ?= "c:\daten\projekte\xpack-arm-none-eabi-gcc-9.2.1-1.1"
  
  SDKHOME-arm-realview ?= "c:\Keil_v528a\ARM\ARMCC\bin"
  SDKHOME-arm-rvheader ?= "c:\Keil_v528a\ARM\ARMCC\include"
