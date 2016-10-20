stdint.h

typedef ciclo_t{
    uint8_t estados;
    uint8_t tiempo_ns;
};

unsigned int modo[3] = { 0, 1, 2 }; //Array de modos para el sw

const ciclo_t modo_0[6] = {
    /* FIJARSE COMO ESTA DECLARADO EL TIEMPO EN RPI_GetArmTimer()-> Load */
    ob 00100001, 10.000; // el tiempo no deberia estar en uint8_t?
    ob 00100010, 2.000; //no se que es ob
    ob 00110100, 1.000;
    ob 00001100, 10.000;
    ob 00010110, 1.000;
    ob 00000000, 0.000;
};

const ciclo_t modo_1[6] = {};

const ciclo_t modo_2[6] = {};

const ciclo_t modo_3[2] = {
	ob 00010010, 1.000;
	ob 00000000, 1.000;
};
