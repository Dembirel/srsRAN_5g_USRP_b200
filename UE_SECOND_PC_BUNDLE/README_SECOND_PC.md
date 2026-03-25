# UE bundle for second PC

Это архив для второго компьютера, где будет запускаться `srsUE` с `USRP B210` по `USB 3`.

Внутри уже лежит:

- собранный `srsUE` с `UHD`
- локальный `UHD`
- `uhd_images`
- конфиг `UE` на `20 MHz`
- запасной конфиг `UE` на `5 MHz`
- reference-конфиги `gNB` для первого ПК

## Что сделать на втором ПК

1. Распаковать архив.
2. Подключить `USRP B210` с serial `343CF04` в `USB 3`.
3. Проверить:

```bash
export PATH=$PWD/uhd-local/bin:$PATH
export LD_LIBRARY_PATH=$PWD/uhd-local/lib:$LD_LIBRARY_PATH
export UHD_IMAGES_DIR=$PWD/uhd_images

uhd_find_devices
uhd_usrp_probe
```

4. Подготовить namespace:

```bash
sudo ip tuntap del name tun_srsue mode tun 2>/dev/null
sudo ip netns del ue1 2>/dev/null
sudo ip netns add ue1
```

5. Запуск `UE` на `20 MHz`:

```bash
cd UE_SECOND_PC_BUNDLE
sudo -E ./run_srsue_20mhz.sh
```

Если не взлетит, запасной вариант:

```bash
cd UE_SECOND_PC_BUNDLE
sudo -E ./run_srsue_5mhz.sh
```

После строки `PDU Session Establishment successful`:

```bash
sudo ip netns exec ue1 ip route add default via 10.45.1.1 dev tun_srsue
sudo ip netns exec ue1 ping -c 4 10.45.1.1
```

Логи:

```bash
tail -f /home/dolaan/ue_b200_20mhz.log
```

или для fallback:

```bash
tail -f /home/dolaan/ue_b200.log
```

## Что запускать на первом ПК

На первом ПК:

- `5GC` как раньше
- `gNB` из `srsRAN_Project`

Для `20 MHz` на первом ПК использовать:

- `/home/dolaan/Desktop/учеба/диплом/srsRAN_5G/srsRAN_Project/configs/gnb_rf_b200_fdd_srsue_20mhz.yml`

Команда:

```bash
export PATH=/home/dolaan/Desktop/учеба/диплом/srsRAN_5G/uhd-local/bin:$PATH
export LD_LIBRARY_PATH=/home/dolaan/Desktop/учеба/диплом/srsRAN_5G/uhd-local/lib:$LD_LIBRARY_PATH
export UHD_IMAGES_DIR=/home/dolaan/Desktop/учеба/диплом/srsRAN_5G/uhd_images

cd /home/dolaan/Desktop/учеба/диплом/srsRAN_5G/srsRAN_Project
sudo -E ./build/apps/gnb/gnb -c configs/gnb_rf_b200_fdd_srsue_20mhz.yml
```
