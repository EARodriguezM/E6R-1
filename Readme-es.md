<h1 align="center">E6R-1: Brazo robótico de 6 GDL impreso en 3D</h1>
<div align="center">

*Brazo robótico de 6 grados de libertad diseñado para la enseñanza de planificación de trayectorias y control, basado en MATLAB/Simulink y ESP32.*

<a href="https://github.com/EARodriguezM/E6R-1/stargazers"><img src="https://img.shields.io/github/stars/EARodriguezM/E6R-1" alt="Stars Badge"/></a> 
<a href="https://github.com/EARodriguezM/E6R-1/network/members"><img src="https://img.shields.io/github/forks/EARodriguezM/E6R-1" alt="Forks Badge"/></a>
<a href="https://github.com/EARodriguezM/E6R-1/pulls"><img src="https://img.shields.io/github/issues-pr/EARodriguezM/E6R-1" alt="Pull Requests Badge"/></a>
<a href="https://github.com/EARodriguezM/E6R-1/issues"><img src="https://img.shields.io/github/issues/EARodriguezM/E6R-1" alt="Issues Badge"/></a>
<a href="https://github.com/EARodriguezM/E6R-1/graphs/contributors"><img alt="GitHub contributors" src="https://img.shields.io/github/contributors/EARodriguezM/E6R-1?color=2b9348"></a>
<a href="https://github.com/EARodriguezM/E6R-1/blob/main/LICENSE"><img src="https://img.shields.io/github/license/EARodriguezM/E6R-1?color=2b9348" alt="License Badge"/></a> 

<a href="https://github.com/EARodriguezM/E6R-1/blob/main/Readme.md"><img src="https://img.shields.io/static/v1?label=&labelColor=505050&message=English README &color=%230076D6&style=flat&logo=google-chrome&logoColor=green" alt="English README"></a>
</div>

-----

## 📖 Descripción general

El **E6R-1** es un manipulador robótico de 6 ejes completamente imprimible. Ofrece un entorno de desarrollo completo para estudiar cinemática de robots, generación de trayectorias y control embebido. El sistema integra:

  * **Mecánica**: estructura robusta impresa en 3D, diseñada para servomotores comerciales estándar.
  * **Firmware**: control embebido en un **ESP32**, conectado a un controlador PWM **PCA9685**.
  * **Software**: un gemelo digital en **MATLAB y Simulink** para simulación, solución de cinemática directa e inversa y control directo del hardware (*hardware-in-the-loop*, HIL).

-----

## 📂 Estructura del proyecto

### 1. Hardware (`/1.Hardware`)

Archivos necesarios para construir el robot físico:

  * **Archivos de impresión**: archivos STL para impresión 3D (p. ej., `base v2.stl`, `drivebig v3.stl`, `link_1.stl`).
  * **Componentes**: pensados para impresión estándar en ABS o PLA.

### 2. Firmware (`/2.Firmware`)

Código fuente y modelos de Simulink para el controlador del robot físico (ESP32):

  * **`Firmware.slx`**: modelo principal de Simulink para el sistema embebido.
  * **`mainController.mlapp`**: interfaz gráfica en MATLAB App Designer para controlar el robot.
  * **`libraries/PCA9685`**: controladores en C++ para el driver de servomotores.
  * **`kinematics/`**: scripts de MATLAB para resolver el movimiento (cinemática directa e inversa).

### 3. Simulación (`/3.Simulation`)

Entorno completamente virtual para probar algoritmos antes de llevarlos al hardware:

  * **`model.slx`**: modelo de simulación de la planta.
  * **`StartupProject.m`**: script que inicializa las rutas y las variables de entorno.

### 4. Documentación (`/5.Documentation`)

  * **`measures.pdf`**: dimensiones físicas y parámetros de Denavit-Hartenberg (DH) del brazo.

### 5. URDF (`/6.URDF`)

  * Archivo de descripción del robot en formato URDF (`robot.urdf`) y mallas para visualización en ROS o MATLAB.

-----

## 🚀 Primeros pasos

### Requisitos

  * MATLAB y Simulink (se recomienda una versión reciente, p. ej., R2023b o superior)
  * Paquete de soporte de Simulink para Arduino/ESP32
  * Impresora 3D (para reproducir el hardware)

### Instalación y configuración

1.  **Clonar el repositorio**:
    ```bash
    git clone https://github.com/EARodriguezM/E6R-1.git
    ```
2.  **Inicializar el entorno de MATLAB**:
    Abra MATLAB, vaya a la carpeta `2.Firmware` o `3.Simulation` y ejecute el script de inicio para agregar las librerías necesarias a la ruta:
    ```matlab
    startup
    % o
    StartupProject
    ```
3.  **Ejecutar la simulación**:
    Abra `3.Simulation/model.slx` para visualizar el comportamiento del robot en un entorno virtual.

-----

## 🧮 Cinemática y control

El proyecto incluye scripts propios para calcular el movimiento del robot.

### Cinemática directa

Calcula la posición del efector final a partir de los ángulos articulares.

```matlab
% Geometría del robot (medidas en mm)
robot.a2 = 427;
robot.a3 = 328.5;
robot.d4 = 116.5;
robot.d5 = 116.5;

% Matriz de configuración inicial (posición de reposo)
gst0 = [1 0 0 robot.d4;
        0 1 0 0;
        0 0 1 robot.a2 + robot.a3 + robot.d5;
        0 0 0 1];

% Ángulos de entrada en grados
angles = [60 30 -50 150 20 -100];

% Cálculo de la cinemática directa
gst_theta = forwardKinematic(robot, gst0, angles);
disp(gst_theta)
```

### Cinemática inversa

Calcula los ángulos articulares necesarios para alcanzar un punto en el espacio.

```matlab
% Matriz de configuración objetivo
gst_theta = [0.66 -0.71 0.23 223.13;
             0.70  0.48 -0.52 5.70;
             0.26  0.51  0.82 603.6;
             0     0     0    1];

% Cálculo de las soluciones
solutions = inverseKinematic(robot, gst0, gst_theta);
disp(rad2deg(solutions))
```

### Matriz antisimétrica y cálculo de twists

Se incluyen funciones auxiliares para calcular matrices de transformación con la fórmula del producto de exponenciales (PoE).

```matlab
syms a2 a3;
omega = [1; 0; 0];    % Eje de rotación
r = [0; 0; a2+a3];
v = cross(r, omega);  % Componente de traslación
xi = [omega; v];      % Twist

T = computeExponential(xi, -0.9961); % Matriz T para el ángulo articular q
```

-----

## 🛠 Arquitectura de hardware

### Electrónica

  * **Microcontrolador**: ESP32 (se recomienda DevKit V1)
  * **Driver de servomotores**: PCA9685 (controlador PWM de 16 canales por I2C)
  * **Actuadores**: servomotores digitales estándar (p. ej., MG996R para la base y servos más livianos para la muñeca)

### Diseño del circuito

El ESP32 se comunica con el PCA9685 por I2C. El modelo `Firmware.slx` gestiona la comunicación I2C y convierte los puntos de la trayectoria en señales PWM.

-----

## 📝 Notas de versión

**Versión actual: 0.0.5**

  * Se agregó la interfaz gráfica en MATLAB App Designer (`mainController.mlapp`).
  * Se integraron los scripts de cinemática directa e inversa.
  * Se actualizaron los archivos STL de `base_rotor` y `connector_straight`.

-----

## 📚 Cómo citar

Si usa este proyecto, cítelo con los metadatos del archivo [`CITATION.cff`](CITATION.cff).

-----

## 🤝 Contribuciones

¡Los *issues* y *pull requests* son bienvenidos!

  * **Issues**: para reportar errores o proponer mejoras relacionadas con el desarrollo del brazo.
  * **Discussions**: para conversaciones generales o ayuda con problemas.

-----

*Creado por [EARodriguezM](https://github.com/EARodriguezM)*

### Algunas preguntas ya fueron respondidas en los Issues; revise los Issues abiertos y cerrados antes de preguntar.
