#ifndef LEDEFFECT_H
#define LEDEFFECT_H

typedef unsigned char  uint8_t;
#define NUMBER_LED 16

void hieuUngSaoBang(uint8_t *dosang, uint8_t *dosangtb, uint8_t speed);
void hieuUngSangDan(uint8_t *dosang, uint8_t *dosangtb);
void hieuUngToiDan(uint8_t *dosang, uint8_t *dosangtb);
void sangTuTraiQuaPhai(uint8_t *dosang, uint8_t *dosangtb);
void tatTuTraiQuaPhai(uint8_t *dosang, uint8_t *dosangtb);
void sangTuPhaiQuaTrai(uint8_t *dosang, uint8_t *dosangtb);
void tatTuPhaiQuaTrai(uint8_t *dosang, uint8_t *dosangtb);
void sangNhayTraiQuaPhai(uint8_t *dosang, uint8_t *dosangtb);
void tatNhayTraiQuaPhai(uint8_t *dosang, uint8_t *dosangtb);
void ledSangDon(uint8_t *dosang, uint8_t const *dosangtb);

#endif // LEDEFFECT_H