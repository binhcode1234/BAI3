# STM32F103C8T6 - External Interrupt Button & LED Control (SPL)

## 📌 Giới thiệu
Sử dụng thư viện SPL cho stm32f103c8t6 :

- Sử dụng **ngắt ngoài (EXTI)** từ nút nhấn tại chân **PB0**.  
- Khi nhấn nút, LED tại chân **PB13** sẽ **đảo trạng thái** (toggle).  
- Đồng thời, LED tại chân **PB12** sẽ **nhấp nháy với chu kỳ 1 Hz** (500ms ON, 500ms OFF).  
- Hàm `Delay_ms()` được xây dựng thủ công bằng **2 vòng for lồng nhau**.  
---

## ⚡ Yêu cầu phần cứng
- Board STM32F103C8T6 (BluePill hoặc tương đương).  
- LED nối với các chân:  
  - **PB12** → LED nhấp nháy 1Hz  
  - **PB13** → LED bật/tắt theo nút nhấn  
- Nút nhấn nối với **PB0** (kéo lên nội bộ, khi nhấn tạo mức LOW).  

---

## 🛠️ Cấu trúc phần mềm
- **GPIO**: cấu hình input (PB0) và output (PB12, PB13).  
- **EXTI**: tạo ngắt ngoài từ PB0.  
- **NVIC**: quản lý ưu tiên và kích hoạt ngắt.  
- **Delay_ms()**: dùng vòng lặp for để tạo trễ (giả định HSI = 8MHz).  

---

## 📂 File chính
- `main.c` → chứa toàn bộ chương trình:
  - `GPIO_Config()` → cấu hình chân.  
  - `EXTI_Config()` → cấu hình ngắt ngoài.  
  - `NVIC_Config()` → cấu hình bộ NVIC.  
  - `EXTI0_IRQHandler()` → xử lý khi nhấn nút.  
  - `Delay_ms()` → hàm trễ bằng vòng for.  

---

## 🚀 Cách build và chạy
1. Cài đặt công cụ build (Keil uVision, STM32 Standard Peripheral Library).  
2. Import code vào project Keil.  
3. Nạp chương trình xuống board STM32F103C8T6 qua ST-Link hoặc USB-UART Bootloader.  
4. Quan sát hoạt động:  
   - LED PB12 nhấp nháy đều 1Hz.  
   - Nhấn nút PB0 → LED PB13 đổi trạng thái.  

---

## 📜 Thư viện sử dụng
```c
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "misc.h"
