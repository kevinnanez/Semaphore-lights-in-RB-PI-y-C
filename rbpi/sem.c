stdint.h

typedef ciclo_t{
    uint8_t estados;
    uint8_t tiempo_ns;
};

const ciclo_t modo_0[10] = {
    /* FIJARSE COMO ESTA DECLARADO EL TIEMPO EN RPI_GetArmTimer()-> Load */
    ob 00100001, 10.000; // el tiempo no deberia estar en uint8_t?
    ob 00100010, 2000; //no se que es ob
    ob 00110100, 1000;
    ob 00001100, 10000;
    ob 00010110, 1.000;
    ob 00000000, 0.000;
}

const ciclo_t modo_1[1] = {
	ob 00010010, 1.000;
	ob 00000000, 1.000;
}