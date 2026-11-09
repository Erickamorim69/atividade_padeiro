#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/sys/printk.h>
#include <stdlib.h>

#define STACK_SIZE 2048
#define PRIORITY 7

int intervalo_padeiro = 1000; // ms
int intervalo_cliente = 1500; // ms

int n_pao = 0;

int max_vitrine = 10;
int saldo_vitrine = 0;

void thread_padeiro(void *p1, void *p2, void *p3) {
    while (1) {
        if (saldo_vitrine < max_vitrine) {
            n_pao++;
            saldo_vitrine++;
            printk("PADEIRO: Pao #%d pronto (Saldo vitrine = %d)\n", n_pao, saldo_vitrine);
        }
        else{
            printk("============= VITRINE CHEIA =================\n");
        }
        k_msleep(intervalo_padeiro);
    }
}

void thread_cliente(void *p1, void *p2, void *p3) {
    while (1) {
        if (saldo_vitrine > 0) {
            saldo_vitrine--;
            printk("CLIENTE: Peguei pao #%d (Saldo vitrine = %d)\n", n_pao, saldo_vitrine);
        }
        k_msleep(intervalo_cliente);
    }
}

K_THREAD_DEFINE(thread_pad, STACK_SIZE, thread_padeiro, NULL, NULL, NULL, PRIORITY, 0, 0);
K_THREAD_DEFINE(thread_cli, STACK_SIZE, thread_cliente, NULL, NULL, NULL, PRIORITY, 0, 0);