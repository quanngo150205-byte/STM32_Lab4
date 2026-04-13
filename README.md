# STM32 Lab 4 – Hệ thống đèn giao thông thông minh (STM32F103C6)

## 1) Giới thiệu project

Đây là đồ án điều khiển **ngã tư đèn giao thông** chạy trên **STM32F103C6** (HAL driver), có các chế độ vận hành và giao diện hiển thị trực quan:

- Đèn giao thông 4 hướng (A/B/C/D).
- LED 7 đoạn quét multiplex để hiển thị thời gian đếm lùi.
- LCD I2C để hiển thị trạng thái hệ thống.
- Nút nhấn với debounce + long press + double click.
- Luồng điều khiển theo **Finite State Machine (FSM)**.
- Có xử lý ưu tiên cho yêu cầu người đi bộ qua đường.

Project phù hợp cho môn Vi điều khiển/Embedded Systems, giúp luyện các kỹ năng:

- Thiết kế state machine đa mode.
- Thiết kế software timer theo tick cố định.
- Tách module driver/UI/logic ứng dụng.
- Đồng bộ hiển thị đa thiết bị (LED giao thông + 7 seg + LCD).

---

## 2) Chức năng chính

### 2.1. Auto mode (chu kỳ đèn tự động)

Hệ thống chạy tuần tự các trạng thái:

- `RED_GREEN`
- `RED_AMBER`
- `GREEN_RED`
- `AMBER_RED`

Mỗi trạng thái cập nhật:

- Màu đèn từng tuyến.
- Bộ đếm thời gian tuyến 1/tuyến 2.
- LED 7 đoạn (đếm lùi).
- LCD (màu + thời gian còn lại).

### 2.2. Manual mode

Cho phép can thiệp thủ công các pha đèn để test/điều khiển trực tiếp:

- `MAN_RED_GREEN`
- `MAN_RED_AMBER`
- `MAN_GREEN_RED`
- `MAN_AMBER_RED`

Trong mode này LCD hiển thị thông tin manual để người vận hành dễ theo dõi.

### 2.3. Config mode

Cho phép chỉnh thời gian theo màu:

- `CONFIG_RED`
- `CONFIG_AMBER`
- `CONFIG_GREEN`

Giá trị sau khi xác nhận sẽ cập nhật vào:

- `RedTime`
- `AmberTime`
- `GreenTime`

và áp dụng lại cho chu kỳ Auto mode.

### 2.4. Chế độ người đi bộ qua đường

Khi đang ở pha có đèn xanh cho một tuyến, nếu có yêu cầu pedestrian:

- Hệ thống rút ngắn thời gian xanh còn ngưỡng an toàn tối thiểu.
- Đồng bộ giảm thời gian đỏ tuyến đối diện để giữ logic chu kỳ.
- LCD nhấp nháy cảnh báo “XIN QUA DUONG”.

### 2.5. Xử lý nút nhấn nâng cao

Module nút nhấn hỗ trợ:

- Nhấn đơn (`isButtonPressed`).
- Nhấn giữ (`isButtonLongPressed`).
- Nhấn đúp (`isButtonDoubleClicked`).
- Debounce theo chu kỳ đọc phím định kỳ.

---

## 3) Kiến trúc & cấu trúc thư mục

## 3.1. Cây thư mục mức cao

```text
STM32_Lab4/
├── Lab4Ex/                  # Firmware STM32CubeIDE
│   ├── Core/
│   │   ├── Inc/             # Header ứng dụng
│   │   └── Src/             # Source ứng dụng
│   ├── Drivers/             # HAL + CMSIS
│   ├── Debug/               # Artifact build (.elf/.hex/.map...)
│   └── STM32Lab4.ioc        # Cấu hình CubeMX
└── Lab4proteus/             # File mô phỏng Proteus
```

### 3.2. Vai trò các module quan trọng

- `main.c`: khởi tạo clock/GPIO/TIM2/I2C, bật ngắt timer định kỳ, gọi callback tick hệ thống.
- `software_timer.[ch]`: bộ timer mềm theo `TICK = 10ms`.
- `button.[ch]`: đọc nút + debounce + sự kiện nhấn đơn/giữ/nhấn đúp.
- `button_event.[ch]`: ánh xạ sự kiện nút thành cờ điều khiển FSM.
- `fsm_automatic.c`: điều khiển chu kỳ đèn tự động.
- `fsm_manual.c`: điều khiển tay các pha đèn.
- `fsm_config.c`: cấu hình thời gian RED/AMBER/GREEN.
- `crossroad.c`: xử lý yêu cầu người đi bộ qua đường.
- `traffic_light.[ch]`: thao tác GPIO điều khiển đèn giao thông.
- `7seg.[ch]`: quét LED 7 đoạn và buffer hiển thị đếm lùi.
- `display_lcd.[ch]`, `i2c_lcd.[ch]`: giao diện LCD I2C.
- `global.[ch]`: trạng thái hệ thống, cờ điều khiển và tham số thời gian.

> Lưu ý: repo có sẵn module `scheduler.[ch]` kiểu cooperative scheduler, nhưng hiện tại vòng chạy chính đang dùng callback timer + FSM theo tick.

---

## 4) Workflow hoạt động của hệ thống

## 4.1. Workflow runtime (trên vi điều khiển)

1. `main()` khởi tạo phần cứng (GPIO, TIM2, I2C).
2. Bật ngắt timer cơ sở (TIM2) với nhịp tick hệ thống.
3. Mỗi tick ngắt sẽ:
   - Cập nhật scheduler timer callback.
   - Giảm bộ đếm software timer.
   - Quét sự kiện nút (event scan).
   - Lấy trạng thái phím (debounce + click parser).
4. FSM đọc các flag/timer để:
   - Chuyển trạng thái đèn.
   - Cập nhật 7 đoạn.
   - Cập nhật LCD.
   - Phản ứng yêu cầu pedestrian.

## 4.2. Workflow điều khiển theo nút (gợi ý)

- Nút Mode: chuyển vòng **Auto → Manual → Config → Auto**.
- Trong Manual: nút control để chuyển pha thủ công.
- Trong Config:
  - Nút tăng/giảm để chỉnh giá trị.
  - Nhấn đúp nút xác nhận để sang bước cấu hình kế tiếp / lưu giá trị.
- Nút Pedestrian: gửi yêu cầu qua đường khi đang ở trạng thái hợp lệ.

## 4.3. Workflow phát triển code

1. Cấu hình ngoại vi bằng `STM32Lab4.ioc` (CubeMX).
2. Sinh mã nền HAL bằng STM32CubeIDE.
3. Viết logic ứng dụng trong `Core/Src` và `Core/Inc`.
4. Build tạo artifact trong `Lab4Ex/Debug` (`.elf`, `.hex`, `.map`).
5. Nạp board thật hoặc mô phỏng bằng Proteus (`Lab4proteus/`).

---

## 5) Mô tả state machine (tóm tắt)

- **INIT**: khởi tạo biến/hardware logic, sau đó vào Auto.
- **AUTO states**: chu kỳ chuẩn của ngã tư.
- **MANUAL states**: ép pha đèn theo thao tác người dùng.
- **CONFIG states**: chỉnh thời gian từng màu theo ràng buộc logic.
- **PEDESTRIAN hook**: chen vào Auto mode khi có yêu cầu hợp lệ.

---

## 6) Gợi ý cải tiến tiếp theo

- Thêm watchdog & cơ chế fail-safe (tất cả đỏ khi lỗi).
- Tách abstraction layer cho phần cứng để unit-test logic FSM trên PC.
- Lưu cấu hình thời gian vào Flash/EEPROM để không mất khi reset.
- Tăng khả năng quan sát bằng UART log hoặc SWV trace.
- Chuẩn hóa tài liệu pinout/sơ đồ nối dây ngay trong repo.

---

## 7) Công cụ & môi trường đề xuất

- **IDE**: STM32CubeIDE.
- **MCU**: STM32F103C6.
- **Firmware stack**: STM32 HAL + CMSIS.
- **Simulation (tùy chọn)**: Proteus.

---

## 8) Ghi chú nhanh cho người mới vào project

- Đọc theo thứ tự nên bắt đầu từ:
  1) `global.h` (hệ state + timer index),
  2) `software_timer.c`,
  3) `button.c` + `button_event.c`,
  4) các file `fsm_*`,
  5) `traffic_light.c`, `7seg.c`, `display_lcd.c`.

- Nếu cần đổi chu kỳ mặc định, sửa các macro:
  - `DEFAULT_REDTIME`
  - `DEFAULT_AMBERTIME`
  - `DEFAULT_GREENTIME`

- Nếu cần đổi tần suất cập nhật hiển thị, xem các macro:
  - `PERIOD_SCAN_7SEG`
  - `PERIOD_LCD_UPDATE`
  - `PERIOD_UPDATE_TIME_BUFFER`

Chúc bạn triển khai và mở rộng project thuận lợi 🚦
