# Embedded GPIO Playground 🚦

This project demonstrates practical usage of **GPIOs** (General Purpose Input/Output) 
on an STM32 microcontroller. Using buttons and LEDs, we implement fundamental concepts such as 
**debouncing**, **bit operations**, **timers**, and **state control**.

The project was originally inspired by a lab exercise, but it has been further developed 
and documented here as a standalone project.

---

## 🎯 Features

- **LED Toggle**: Toggle LEDs on/off by pressing a button.
- **Software Debouncing**: Debounce buttons using a `CDebouncer` class.
- **Chasing Light**: Sequential running light across LEDs (different timer strategies).
- **Configurable Light**: Adjust direction and speed of the light using buttons.
- **Timer Class**: Manage waiting times flexibly without using blocking `sleep`.

---

## 🛠 Hardware Setup

- STM32 Nucleo board (e.g. STM32F4xx or similar)  
- Breadboard with:
  - 8 LEDs + resistors
  - 8 push buttons
- USB Logic Analyzer (e.g. used with **PulseView**)

---

## 💻 Software Setup

- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)  
- Mbed OS project structure  
- PulseView for logic analysis  

---

## 📂 Project Structure

---

## 🚀 Getting Started

1. Clone the repository  
   ```bash
   git clone https://github.com/yassinejabnoun/gpio-playground.git
2. Import the project into STM32CubeIDE.
3. Connect the hardware (LEDs, buttons, logic analyzer).
4. Build & flash the program.

---

## 📸 Showcase

<img width="533" height="387" alt="image" src="https://github.com/user-attachments/assets/b9840f00-b451-4f27-8a2b-52eed87bfabb" />
<img width="445" height="303" alt="image" src="https://github.com/user-attachments/assets/b984b8a5-8a09-433c-ac71-4c007e328a12" />

---

## 📜 License

MIT License – free to use for personal or professional projects.




