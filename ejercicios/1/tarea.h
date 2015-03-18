#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

enum {
	NOMBRE_TAREA = 0,
	DESC_TAREA,
	TAREA_ID,
	NOMBRE_USUARIO_T,
	T_PRIORIDAD,
	__TAREAS_MAX
};

#define TAREAS_MAX (__TAREA_MAX - 1)

#define xfree(ptr)      free((void *)ptr);

struct tarea {
	struct list_head head;
	const char 	*nombre_tarea;
	const char 	*desc_tarea;
	int 		tarea_id;
	const char 	*nombre_usuario_t;
	int 		t_prioridad;
	uint32_t 	flags;
};

struct tarea *tarea_alloc(void);
void tarea_free(struct tarea *);

bool tarea_is_set(const struct tarea *t, uint16_t attr);

void tarea_unset(struct tarea *t, uint16_t attr);

void tarea_set_data(struct tarea *t, uint16_t attr, const void *data,
			       uint32_t data_len);
void tarea_set_u32(struct tarea *t, uint16_t attr, uint32_t data);
void tarea_set_str(struct tarea *t, uint16_t attr, const char *data);

const void *tarea_get_data(struct tarea *t, uint16_t attr);
uint32_t tarea_get_u32(struct tarea *t, uint16_t attr);
const char *tarea_get_str(struct tarea *t, uint16_t attr);

int tarea_snprintf(char *buf, size_t size, struct tarea *t);
