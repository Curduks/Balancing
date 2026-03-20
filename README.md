# Reaction Wheel Balancing System (STM32)

STM32F446RE 기반의 리액션휠 밸런싱 시스템입니다.  
IMU(MPU6050)로 자세를 추정하고, PID 제어로 모터를 구동해 특정 각도에서 균형을 유지합니다.

## Demo
![demo-1](https://github.com/user-attachments/assets/b2cecd11-195c-4238-af82-f6b1c43db167)
![demo-2](https://github.com/user-attachments/assets/d39afd44-6861-44fd-86ca-28446da09298)
![demo-3](https://github.com/user-attachments/assets/e8181e03-c8ec-44f1-9f09-8656bafafaef)
<img width="600" height="489" alt="화면 캡처 2026-03-20 160052" src="https://github.com/user-attachments/assets/17b43ff9-6098-4296-b599-84bbe12abce8" />

- Full video: https://github.com/user-attachments/assets/a24ddeb2-01e7-45bb-adb2-de60699e0d9e

## 프로젝트 개요

이 프로젝트는 임베디드 제어(PID), 센서 융합, 실시간 태스크 설계를 실제 하드웨어에 적용해 보는 것을 목표로 제작했습니다.

- 제어 대상: 반작용 기반 1축 밸런싱 구조물
- 제어 목표: 목표 각도 부근에서 자세 안정화
- 개발 환경: STM32CubeIDE + HAL + FreeRTOS

## 사용 기술

| 구분 | 내용 |
|---|---|
| MCU | STM32F446RE (NUCLEO-F446RE) |
| Language | C |
| Framework | STM32 HAL, CMSIS-RTOS v2, FreeRTOS |
| Sensor | MPU6050 (I2C1) |
| Actuator | BLDC Motor (PWM + DIR + BRAKE) |
| Debug | UART2 (115200) |

## 하드웨어 구성

| 부품 | 수량 | 비고 |
|---|---:|---|
| NUCLEO-F446RE | 1 | 메인 컨트롤러 |
| MPU6050 | 1 | 자세 측정 IMU |
| BLDC Motor (Nidec BL4234-24V) | 1 | 반작용휠 구동 |
| 볼 베어링 (내경 4 / 외경 9) | 2 | 구조물 회전부 |
| M3x10 나사 | 11 | 조립용 |
| M4x10 나사/너트 | 12 | 조립용 |

## 3D 설계 파트

| body 1 | body 2 | body 3 | wheel | pole |
|---|---|---|---|---|
| <img width="220" alt="body1" src="https://github.com/user-attachments/assets/fbf7101b-74ba-43cd-ba5c-60df2a369a08" /> | <img width="220" alt="body2" src="https://github.com/user-attachments/assets/a1322cee-770d-40ed-aa4f-54aedc3a6cc7" /> | <img width="220" alt="body3" src="https://github.com/user-attachments/assets/87d4c657-b79e-4a5a-86b3-226f9d04fef7" /> | <img width="220" alt="wheel" src="https://github.com/user-attachments/assets/0ac86609-3615-4756-8bc7-6317f8e63265" /> | <img width="220" alt="pole" src="https://github.com/user-attachments/assets/87cdca5e-af6c-4f27-8f8b-40aa6d2f0899" /> |

## 제어 로직 요약

1. IMU 초기화 및 센서 설정
- 샘플레이트: 1000Hz 설정
- 자이로/가속도 범위 설정 후 주기적으로 값 읽기

2. 자세 추정
- 자이로 적분 + 가속도 기반 각도 계산
- 상보필터(Complementary Filter, `alpha=0.98`)로 pitch/roll 융합

3. PID 제어
- 오차: `targetAngle - measuredAngle`
- 게인: `Kp=10.4`, `Ki=5.0`, `Kd=0.22`
- 적분 제한(anti-windup): `Imax=70`
- 출력 제한: `MAX_PWM=60`

4. 모터 구동
- PWM(TIM3 CH1) + 방향(DIR) + 브레이크(BREAK) 핀 제어
- 안전 구간(`pitch`가 27~57도 범위 밖)에서는 모터 정지

## 소프트웨어 구조

```text
balancing/
├─ Core/Inc/
│  ├─ mpu6050.h
│  └─ pid.h
├─ Core/Src/
│  ├─ freertos.c      # 제어 태스크 생성/루프
│  ├─ mpu6050.c       # IMU 드라이버 + 자세 추정
│  ├─ pid.c           # PID 계산 + 모터 제어
│  ├─ tim.c           # PWM 설정(TIM3)
│  ├─ i2c.c           # IMU 통신(I2C1)
│  └─ usart.c         # UART 디버깅
└─ balancing.ioc      # CubeMX 설정 파일
```

## 빌드 및 실행

1. `STM32CubeIDE`에서 프로젝트 열기 (`balancing`)
2. 타겟 보드: `NUCLEO-F446RE` 연결
3. Build 후 Flash
4. 전원 및 모터 드라이브 배선 확인 후 동작 테스트
