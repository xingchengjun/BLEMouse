#include <BleMouse.h>
#include <WiFi.h>

BleMouse bleMouse("ps2blue", "Espressif", 100);

const int xPin = 32;     // X 轴 ADC 引脚
const int yPin = 33;     // Y 轴 ADC 引脚
const int btPin = 15;    // 按钮引脚
const int adcRange = 4095; // ADC 的最大值（12位）
const float xCentreRaw = 1797.0; // 假设的X轴中心值（对于12位ADC，2048是中心）可以改为自己遥感的中心数值
const float yCentreRaw = 1885.0; // 假设的Y轴中心值（可能需要调整）
const int movePixels = 10; // 每次鼠标移动的像素数
const int delayMs = 50;   // 每次移动后的延迟时间（毫秒）

float xOffset = 0.0;     // X轴偏移量（累积的）
float yOffset = 0.0;     // Y轴偏移量（累积的）

void setup() {
  analogSetWidth(12); // 设置ADC分辨率为12位
  pinMode(btPin, INPUT_PULLUP); // 设置按钮引脚为上拉输入
  Serial.begin(115200); // 初始化串口
  Serial.println("Starting BLE work!");
  bleMouse.begin();
}

void loop() {
  if (bleMouse.isConnected()) {
    // 读取ADC值
    int xRaw = analogRead(xPin);
    int yRaw = analogRead(yPin);

    // 计算偏移量（从中心值开始）
    float xDiff = xRaw - xCentreRaw;
    float yDiff = yRaw - yCentreRaw;

    // 根据偏移量计算位移（这里可以调整比例因子来控制灵敏度）
    float xMove = xDiff * 0.01; // 假设的比例因子，可能需要调整
    float yMove = yDiff * 0.01;

    // 累积偏移量（用于平滑移动）
    xOffset += xMove;
    yOffset += yMove;

    // 将累积偏移量转换为步数
    int stepsX = xOffset / movePixels;
    int stepsY = yOffset / movePixels;

    // 执行X轴移动
    for (int i = 0; i < abs(stepsX); i++) {
      bleMouse.move((stepsX > 0 ? -1 : 1) * movePixels, 0);
      delay(delayMs);
    }
    // 重置X轴偏移量（仅当完成所有步骤时）
    if (stepsX != 0) {
      xOffset -= stepsX * movePixels;
    }

    // 执行Y轴移动
    for (int i = 0; i < abs(stepsY); i++) {
      bleMouse.move(0, (stepsY > 0 ? -1 : 1) * movePixels);
      delay(delayMs);
    }
    // 重置Y轴偏移量（仅当完成所有步骤时）
    if (stepsY != 0) {
      yOffset -= stepsY * movePixels;
    }

    // 检查按钮
    if (digitalRead(btPin) == LOW) {
      delay(200); // 防抖
      bleMouse.click(MOUSE_LEFT); // 左键点击
    }
  }
  delay(50); // 保持循环的频率
}