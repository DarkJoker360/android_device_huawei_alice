*PATCHES FOR HUAWEI P8 LITE*

- bt.patch in system/bt

- surfaceflinger.patch in frameworks/native

- toggle.patch in frameworks/opt/telephony

- __vsprintf_chk.cpp, you can find it in bionic/libc/bionic, edit and add at line 46 " // " next to ""__fortify_chk_fail("vsprintf: prevented write past end of buffer", 0);""

the result is:  ""//__fortify_chk_fail("vsprintf: prevented write past end of buffer", 0);""

and add at line 47 ""result = (int)dest_len_from_compiler - 1;"" under the f of line 46,

the final result is: 

**LINES 46-47**

    //__fortify_chk_fail("vsprintf: prevented write past end of buffer", 0);
  }     result = (int)dest_len_from_compiler - 1;
