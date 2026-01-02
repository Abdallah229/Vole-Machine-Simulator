# VOLE Machine Simulator (CLI Version)

A C++ command-line interface (CLI) simulation of a VOLE machine architecture. This project emulates the fetch-decode-execute cycle of a CPU, allowing users to load programs, execute machine code instructions, and inspect the state of memory and registers.

> **Note:** This is the **CLI version** of the project. It runs entirely in the terminal without a graphical user interface.

## 📂 Project Structure

The project relies on a modular architecture using the following components:

* **Machine:** The main controller that integrates the CPU and Memory.
* **CPU:** Handles the fetch-decode-execute cycle (Fetch, Decode, Execute).
* **CU (Control Unit):** Manages instruction decoding and control signals (Load, Store, Move, Jump, Halt).
* **ALU (Arithmetic Logic Unit):** Performs arithmetic and bitwise operations (Integer/Float Addition, AND, OR, XOR, Rotate).
* **Memory:** Simulates the machine's RAM (256 cells).
* **Register:** Simulates the CPU's general-purpose registers.
* **Methods:** Utility functions for Hex/Binary conversion, file reading, and input validation.

## 🚀 Getting Started

### Prerequisites

To compile and run this project, you need:

* A C++ compiler (e.g., `g++` or `clang++`)
* Standard C++11 support or higher

### Compilation & Running

Navigate to the source code directory and compile the project using the following commands:

```bash
cd ./CLI/Code
```

```bash
g++ *.cpp -o machine_simulator
```

```bash
./machine_simulator run

```

## 🎮 How the CLI Works

The simulator uses an **interactive command-line interface**.  
When you launch the application, you will be greeted by the **Vole Machine welcome screen** and a navigation menu.

---

## 1️⃣ Main Menu Navigation

The program utilizes a **keyboard-driven menu system**:

* **Navigation:** Use the **Arrow Keys (↑ / ↓)** to scroll through options  
* **Selection:** Press **Enter** to select an option  

### Menu Options

* **Use Vole Machine**: Starts the simulation  

* **Authors**: Displays the credits for the developers  
  * Loai Hataba  
  * Abdullah Mohammed  
  * Hossam Abdelaziz  

* **Exit**: Closes the application  

---

## 2️⃣ Loading Instructions

Once you start the **Vole Machine**, you will be prompted to choose an input method:

* **(M) Manually**  
  Type your instructions directly into the console as a **hexadecimal string**.

* **(F) By File**  
  Provide the full path to a `.txt` file containing your machine code  
  > Example:  
  `C:\Users\Name\Documents\program.txt`

---

## 3️⃣ Simulation & Visualization

* **Start Address**  
  Specify the starting memory address for your program (e.g., `10` or `20`).

* **Real-time Feedback**  
  Instructions are executed **step-by-step** with a visual delay  
  (~ **1.75 seconds per step**).

* **State Output**  
  After every instruction, the console clears and redraws:
  * **Memory Map**  
    A `16 × 16` grid showing all **256 memory cells**  
    * Active cells are highlighted in **Green**
  * **Registers**  
    Displays current values of registers **R0 through RF**
  * **Halt & Jump Notifications**  
    The system notifies you when:
    * A **Jump** occurs  
    * The program **Halts**

---

## ⚙️ Functionalities & Instruction Set

The simulator parses **4-character hexadecimal instructions**  
(e.g., `10AF`) and executes them based on the **OpCode**  
(the **first character**).

### 🧾 Instruction Table

| OpCode | Instruction | Description |
|------:|------------|-------------|
| 1 | LOAD | Load contents of memory address `XY` into register `R` |
| 2 | LOAD | Load immediate value `XY` into register `R` |
| 3 | STORE | Store contents of register `R` into memory address `XY` |
| 4 | MOVE | Copy value from register `R` to register `S` |
| 5 | ADD | Add contents of registers `S` and `T` (Two’s Complement) and store in `R` |
| 6 | FLOAT | Add contents of registers `S` and `T` (Floating Point) and store in `R` |
| 7 | OR | Bitwise OR of `S` and `T`, stored in `R` |
| 8 | AND | Bitwise AND of `S` and `T`, stored in `R` |
| 9 | XOR | Bitwise XOR of `S` and `T`, stored in `R` |
| A | ROTATE | Rotate register `R` cyclically right by `X` steps |
| B | JUMP | Jump to memory address `XY` if `register R == register 0` |
| C | HALT | Stop execution |

---

## 🎓 Credits

Created for the **Faculty of Computers and Artificial Intelligence for CS213-OOP course**,  
**Cairo University**.