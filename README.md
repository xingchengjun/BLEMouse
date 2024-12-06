PS2bleMouse
介绍
基于ESP32和ps2遥感的蓝牙鼠标项目

使用教程： 基于ESP32的BLE无线鼠标控制

所需硬件： ESP32开发板：用于运行代码和处理蓝牙连接。 ps2模拟摇杆：用于检测方向输入。

所需软件： Arduino IDE：用于编写和上传代码到ESP32。 ESP32开发板支持：在Arduino IDE中安装ESP32的Board Manager支持。 BleMouse库：用于实现蓝牙鼠标功能。 WiFi库（尽管在这个示例中未使用，但BleMouse库的初始化需要它）。

步骤： 1.安装Arduino IDE和ESP32支持： 下载并安装Arduino IDE。 打开Arduino IDE，进入文件 > 首选项，在“附加开发板管理器网址”中添加https://dl.espressif.com/dl/package_esp32_index.json。 打开工具 > 开发板 > 开发板管理器，搜索ESP32并安装。 安装BleMouse库： 打开工具 > 管理库 > 导入zip库 ESP32-BLE-Mouse-master

连接硬件： 遥感 ESP32 GND---->GND +5V---->3v3 VRX---->32 VRY---->33 SW----->15

修改代码 根据需要调整xCentreRaw和yCentreRaw值，以匹配你的摇杆中心值。 选择正确的开发板和端口（工具 > 开发板 > ESP32 Dev Module，工具 > 端口 > 选择你的端口）。 上传代码到ESP32。 配置和使用： 等待ESP32启动并完成BLE初始化。 在你的电脑或平板上打开蓝牙设置，查找名为ESP32的设备并连接。 连接成功后，移动摇杆将控制鼠标的移动，按下按钮将执行鼠标左键点击。

调试和优化： 如果鼠标移动不够灵敏或过于灵敏，可以调整xDiff * 0.01和yDiff * 0.01中的比例因子。 如果需要更平滑的移动，可以调整movePixels和delayMs的值。 注意事项： 确保ESP32有足够的电源供应，特别是在连接多个外设时。 在连接蓝牙设备之前，确保电脑或平板的蓝牙功能已开启，并且没有其他设备占用相同的蓝牙名称。 如果遇到连接问题，尝试重启ESP32和蓝牙设备，或重新扫描蓝牙设备。 通过上述步骤，你应该能够成功使用ESP32和模拟摇杆创建一个无线蓝牙鼠标控制器。
