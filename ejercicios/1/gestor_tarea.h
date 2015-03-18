#include "tarea.h"

enum {
	GESTOR_TAREAS_TAREAS,
	GESTOR_TAREAS_NUM_TAREAS,
	__GESTOR_TAREAS_MAX
};

#define GESTOR_TAREAS_MAX (__GESTOR_TAREAS_MAX - 1)

#define xfree(ptr)      free((void *)ptr);

struct gestor_tarea;

struct gestor_tarea *gestor_tareas_alloc(void);
void gestor_tareas_free(struct gestor_tarea *gt);

bool gestor_tareas_is_set(const struct gestor_tarea *gt, uint32_t attr);

void gestor_tareas_unset_tarea(struct gestor_tarea *gt, uint32_t pos);

void gestor_tareas_set_tarea(struct gestor_tarea *gt, const void *data);

const void *gestor_tareas_get_data(struct gestor_tarea *gt, uint16_t attr, uint32_t pos);
uint32_t gestor_tareas_get_u32(struct gestor_tarea *gt, uint16_t attr);
const char *gestor_tareas_get_str(struct gestor_tarea *gt, uint16_t attr);
struct tarea *gestor_tareas_get_tarea(struct gestor_tarea *gt, uint16_t ttr, uint32_t pos);

int gestor_tareas_snprintf(char *buf, size_t size, struct gestor_tarea *gt);
