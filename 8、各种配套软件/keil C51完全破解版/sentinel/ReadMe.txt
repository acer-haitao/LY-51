                      SENTINEL SYSTEM DRIVER VERSION 5.39.2
                                 README.TXT
                 Copyright (C) 1991-2001 Rainbow Technologies, Inc.
                            All Rights Reserved
                               
******************************  IMPORTANT NOTE *******************************
When you run the setup.exe program to install the driver, it will
automatically update your version of the Windows Installer if necessary. It
will not provide any prompts before doing this. If you are not sure you want
to update the Windows Installer, do not run this program.
******************************  IMPORTANT NOTE *******************************                 

 The Sentinel System Drivers provide a communication path between your
 protected application and the Sentinel key. The driver allows multiple
 programs to all access the Sentinel key on a multi-tasking operating system.

 This version of the driver contains a new installation method using the new
 Windows Installer. This allows you to install the driver on any Windows
 9x/NT/2000 system just like a regular application. This readme file describes
 the installation procedure for the Sentinel System Driver.

 If you are installing the driver for DOS, Windows 3.x, OS/2, or any non-Intel
 Windows NT machine, you must use the old installer. The old installer is
 located in the "Legacy" directory of the driver media. Also, the old
 installer has been kept to allow developers that are not yet ready to migrate
 to the Windows Installer to keep their old installation methods. There are
 some limitations to doing this, however. The old installer does not support
 installing only the USB driver; you must use the new installer to do that.

 This README file provides information on product installation,
 new features, last-minute news, and where to go for more
 information or to report problems. for more information
 refer to the complete documentation: SentinelDriverInstall_Start.htm.

-----------------------
 TABLE OF CONTENTS
-----------------------

  1.0 Installing the Product
      1.1 Installation
      1.2 Installation Options
      1.3 Merge Modules
  2.0 What's New in This Release?
      2.1 Changes Since the Last General Release (PD-5.39)
      2.2 Changes Since PD-5.38
      2.3 Problems Fixed
  3.0 Late-breaking News
  4.0 Known Problems
  5.0 Where to Go Next?
  6.0 Reporting Problems

-------------------------------
 1.0 INSTALLING THE PRODUCT
-------------------------------

 This section contains what you should know before you
 install this product as well as installation instructions.

--------------------------
 1.1 Installation
--------------------------

 1. If you have the driver on CD, place the CD in the computer and it should
    automatically run the installation program.

 2. Otherwise, run the "setup.exe" from the root directory of the driver
    media.

 3. If you do not have the correct version of the Windows Installer, it will
    automatically be installed for you.

 4. If setup detects an older version of the Sentinel System Driver, you will
    be prompted to confirm the upgrade. The older version is uninstalled
    immediately after you confirm the upgrade. If you cancel out of the
    installation after this, the older version will not still be installed.

 5. Select either "complete" or a "custom" installation. "Complete" will
    install both the parallel and USB driver.

 6. If you select "custom," you can choose whether to install parallel, USB,
    or both. Keep in mind that if your operating system does not support USB,
    the installer will not install it even if you select it.

 7. Continue on the installation and select "Install."

 8. Depending on the operating system and the configuration of the computer,
    you may be prompted to reboot.

-------------------------------------
1.2 Modification/Removal Instructions
-------------------------------------
 1. Go to the Control Panel from the "Start" menu.

 2. Select "Add/Remove Programs."

 3. Look for the item that says "Sentinel System Driver" and select it.

 4. The installer will allow you to modify, repair, or remove the
    installation; select which option you would like and follow the
    instructions.

 5. If you select "modify," you can add in or remove the parallel or USB
    driver later.

 6. Depending on the operating system and the configuration of the computer,
    you may be prompted to reboot.

------------------------
1.3 Installation Options
------------------------
 The Sentinel System Driver Installer offers many different command-line
 options to control the installation. This allows developers to install the
 driver on their end users' systems without prompts. For more information on
 these options, refer to the online guide, SentinelDriverInstall_start.htm.

-----------------
1.4 Merge Modules
-----------------
 The driver contains three merge modules which will allow you to "merge" the
 Sentinel System Driver installation into your own package. This can only be
 done if you are using a Microsoft Windows Installer package. For more
 information on doing this refer to the online guide, 
 SentinelDriverInstall_start.htm.


---------------------------------
 2.0 WHAT'S NEW IN THIS RELEASE?
---------------------------------
 This section contains information on new features and fixed problems for this
 release.

-----------------------------------------------------
 2.1 Changes Since the Last General Release (PD-5.39)
-----------------------------------------------------
 1. The USB driver is Microsoft Windows Hardware Quality Labs (WHQL)
    certified for Windows 2000. The driver is unchanged from the 5.39.0
    version but has undergone the WHQL tests to be certified for use on
    Windows 2000 operating systems. This allows for Windows 2000 Logo
    compliance for applications that use the Sentinel SuperPro USB hardware
    keys.

 2. There have been some changes to the merge modules, including some new
    custom actions. These are fully documented in the merge module
    online guide, SentinelDriverInstall_Start.htm.

 3. The Sentinel System Driver installer and merge modules pass all the
    Microsoft ICE (Internal Consistency Evaluation) tests. Passing these
    tests is required for Windows 2000 logo compliance. Although the 
    installer is not Windows 2000 logo compliant, when the merge modules 
    are used in another installer, they will not cause the installer to fail
    due to ICE tests.

 4. The merge module file names had spaces in them which caused them to fail
    Microsoft's Internal Consistency Evaluation (ICE) tests. Thus, the merge
    modules had to be renamed to conform to this change. This may require
    re-adding the merge modules to your installation project if you are using
    them. It may be possible to just rename the modules back to their
    original filenames, depending on your installer package.

--------------------------
 2.2 Changes Since PD-5.38
--------------------------
 1. The USB SuperPro driver can be installed alone. Before this version, you
    always had to have the parallel driver installed to use the USB driver. In
    order for you application to take advantage of this new feature, it will
    have to be rebuilt using the latest libraries.

 2. You can prevent the virtual device driver (VDD) from being installed on
    Windows NT or 2000. The VDD is only necessary for older DOS and Win16
    applications.

 3. The 5.39 driver supports the new SuperPro Net hardware key. The SuperPro
    Net cannot be seen on any driver version before 5.39.

 4. The driver uses the new Windows Installer (version 1.1) released with
    Windows 2000. This installer supports all Windows operating systems back
    to Windows 95. The Microsoft Windows Installer is part of the initiative
    to reduce the total cost of ownership (TCO) for customers by enabling
    them to efficiently install and configure products and applications. For
    more information visit Microsoft's MSDN web site.

 5. As a part of the Microsoft Windows Installer, the 5.39 driver contains
    "merge modules" that can be incorporated directly into your own installer
    providing seamless integration. See the documentation on using these
    merge modules in the online manual, SentinelDriverInstall_Start.htm.

--------------------
 2.3 Problems Fixed
--------------------

 1. In version 5.39.0, many customers experienced a pop-up message displaying
    "Installation Failed." This generally meant the USB portion of the
    install had not completed successfully. This has been fixed.

 2. Version 5.39.0 would only install files to its default installation
    directory. It can now be installed to any drive. Since this is a driver,
    however, it should always be installed to a local hard drive that is
    always available. Logically, the best drive to use is your "C:" drive.

 3. Corrections have been made to the merge module documentation. Also, the
    documentation has been extended to give more examples of how to use the
    merge modules.

 4. Several customers had trouble installing the driver on non-English
    machines. This issue was related to other installation problems with the
    USB driver. It has been fixed and has been tested on both Western and
    Eastern systems. The driver installation directory must not contain
    double-byte characters, but will otherwise install on these systems.


------------------------
 3.0 LATE-BREAKING NEWS
------------------------

 None.


--------------------
 4.0 KNOWN PROBLEMS
--------------------

 1. The Legacy installer cannot install just the USB driver. It installs
    only the parallel driver, or both the parallel and USB driver.
    
 2. The Legacy installer may not always correctly update the USB driver on
    a system where the USB driver is already installed. Updating the USB
    driver may require a manual update via the device manager. This only
    occurs in Windows 2000.
    
 3. When installing the driver on a system that uses a double-byte language,
    the install directory cannot contain double-byte characters. The install
    directory should only contain ASCII characters.
    
 4. Microsoft WHQL certification only applies only to the USB driver.  
    Microsoft only certifies Plug 'n' Play drivers and the parallel port
    devices are not Plug 'n' Play.
    
 5. USB is no longer supported on Windows 95 systems. Because older driver 
    versions supported this, it may still work; however, it has not been
    tested.

-------------------------
 5.0 WHERE TO GO NEXT?
-------------------------

 For information on including the Sentinel System Driver in your own
 product installation, and for information on using the Windows Installers
 merge modules, see the online installation guide,
 SentinelDriverInstall_start.htm.


-------------------------
 6.0 REPORTING PROBLEMS
-------------------------

 If you find any problems, please contact Rainbow Technical Support
 using any of the following methods:

 CORPORATE HEADQUARTERS NORTH AMERICA AND SOUTH AMERICA
 ---------------------------------------------------------
 Rainbow Technologies, Inc.
 Internet      http://www.rainbow.com
 E-mail        techsupport@irvine.rainbow.com
 Telephone     (800) 959-9954 (6:00 a.m.-6:00 p.m. PST)
 Fax           (949) 450-7450

 AUSTRALIA
 ---------------------------------------------------------
 Rainbow Technologies (Australia) Pty Ltd.
 E-mail        techsupport@au.rainbow.com
 Telephone     (61) 3 9820 8900
 Fax           (61) 3 9820 8711

 CHINA
 ---------------------------------------------------------
 Rainbow Information Technologies (China) Co.
 E-mail        sentinel@isecurity.com.cn
 Telephone     (86) 10 8266 3936
 Fax           (86) 10 8266 3948

 FRANCE, SPAIN, PORTUGAL, ITALY, GREECE, TURKEY, ISRAEL,
 MIDDLE EAST, NORTH & CENTRAL AFRICA
 ---------------------------------------------------------
 Rainbow Technologies FRANCE
 E-mail        techsupport@fr.rainbow.com
 Telephone     (33) 1 41.43.29.00
 Fax           (33) 1 46.24.76.91

 GERMANY, AUSTRIA, SWITZERLAND, POLAND, CZECH REPUBLIC,
 SLOVAKIA, HUNGARY, ROMANIA, CROATIA, RUSSIA & FORMER
 RUSSIAN STATES
 ---------------------------------------------------------
 Rainbow Technologies GERMANY
 E-mail        techsupport@de.rainbow.com
 Telephone     (49) 89.32.17.98.0
 Fax           (49) 89.32.17.98.50

 TAIWAN AND SOUTHEAST ASIA
 ---------------------------------------------------------
 Rainbow Information Technologies (Taiwan) Co., Ltd.
 E-mail        techsupport@tw.rainbow.com
 Telephone     (886) 2 2570-5522
 Fax           (886) 2 2570-1988

 UNITED KINGDOM, IRELAND, SWEDEN, NORWAY, DENMARK,
 FINLAND, NETHERLANDS, BELGIUM, LUXEMBOURG, SOUTH AFRICA
 ---------------------------------------------------------
 Rainbow Technologies UK
 E-mail        techsupport@uk.rainbow.com
 Telephone     (44) 1932.579200
 Fax           (44) 1932.570743

 OTHER COUNTRIES
 ---------------
 Customers not in countries listed above, please contact your local
 distributor.



[readme, June 13, 2001, V. 1]