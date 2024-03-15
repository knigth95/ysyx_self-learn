#include <nvboard.h>

<<<<<<<<<<<<<<  ✨ Codeium Command 🌟 >>>>>>>>>>>>>>>>
+static TOP_NAME dut;
+
+int main(int argc, char* argv[])
+{
-int main(int argc,char* argv[]){
    nvboard_bind_all_pins(&dut);
    nvboard_init();
+
+    while (nvboard_update())
+    {
-    while(1){
-        nvboard_update();
    }
+
    nvboard_quit();
+
+    return 0;
}
+
<<<<<<<  29119d75-e015-4275-a145-35c39a8cbe68  >>>>>>>