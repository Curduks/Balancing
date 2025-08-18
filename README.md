# 개요
본 프로젝트는 제어 공학 수업때 이론으로만 배운 PID 제어를 하드웨어와 결합한 실시간 시스템으로 구현해보기 위해 시작 되었습니다.

주요 학습 목표는 다음과 같았습니다

PID 제어기 설계: P, I, D 각 파라미터가 시스템의 응답 특성(오버슈트, 정상상태 오차 등)에 미치는 영향을 직접 체험하고, 안정적인 제어기를 설계하는 경험을 쌓고자 했습니다.

센서 데이터 처리: IMU 센서(가속도/자이로)로부터 출력되는 노이즈 섞인 데이터를 필터링하고 융합하여, 시스템의 현재 상태를 최대한 정확히 추정하는 능력을 기르고자 했습니다.

# 기술 스택 및 개발 환경
+ **MCU:** STM32F446RE (Cortex M4)
+ **개발 보드:** NUCLEO-F446RE
+ **사용 언어:** C (HAL)
+ **RTOS:** FreeRTOS
+ **개발 툴:** STM32CubeIDE

# 필요한 구성요소
## 3D 프린터 모델링
| body 1                    | body 2                                              | body 3                                                | wheel                            | pole                                                          |
| --------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------- | ------------------------------------------------------------ |
|<img width="300" height="300" alt="body1" src="https://github.com/user-attachments/assets/fbf7101b-74ba-43cd-ba5c-60df2a369a08" />|<img width="300" height="300" alt="body2" src="https://github.com/user-attachments/assets/a1322cee-770d-40ed-aa4f-54aedc3a6cc7" />|<img width="300" height="300" alt="body3" src="https://github.com/user-attachments/assets/87d4c657-b79e-4a5a-86b3-226f9d04fef7" />|<img width="300" height="300" alt="wheel" src="https://github.com/user-attachments/assets/0ac86609-3615-4756-8bc7-6317f8e63265" />|<img width="300" height="300" alt="pole" src="https://github.com/user-attachments/assets/87cdca5e-af6c-4f27-8f8b-40aa6d2f0899" />|

## 하드웨어 부품
|부품        |설명        |개수        |
|-----------|------------|------------|
|<img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/cb532563-37fd-4679-b258-04c12993539b" />|볼베어링 내경4 외경9 폭4	| 2개 |
|<img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/63e14612-8e98-4439-8afa-ac412a591179" />|M3 나사 M3x10mm	| 11개 |
|<img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/63e14612-8e98-4439-8afa-ac412a591179" />|M4 나사 및 너트 M4x10mm	| 12개 |
|<img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/f153ba67-0901-4fa2-8ed5-4bae1c60f36e" />|구동컨트롤러 내장형 BLDC (Nidec BLDC Motor BL4234-24V)| 1개 |
|<img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/dadaab83-cab9-489c-a8d2-4e6c23f7bf5c" />|MPU6050 (IMU센서) | 1개 |
