#include <string.h>
#include "gestor_tarea.h"

#define GESTOR_TAREAS_MAXT 10

struct gestor_tarea {
	struct list_head tareas;
	uint32_t num_tareas;
	uint32_t flags;
};

struct gestor_tarea *gestor_tareas_alloc(void)
{
	struct gestor_tarea *gt = malloc(sizeof(struct gestor_tarea));

	if (gt == NULL)
		return NULL;

	INIT_LIST_HEAD(&gt->tareas);
	return gt;
}

void gestor_tareas_free(struct gestor_tarea *gt)
{
	int i;
	struct tarea *t, *tmp;

	list_for_each_entry_safe(t, tmp, &gt->tareas, head) {
		list_del(&t->head);
		tarea_free(t);
	}

	xfree(gt);
}

bool gestor_tareas_is_set(const struct gestor_tarea *gt, uint32_t attr)
{
	return gt->flags & (1 << attr);
}

void gestor_tareas_unset_tarea(struct gestor_tarea *gt, uint32_t pos)
{
	int i = 0;
	struct tarea *t, *tmp;

	if (pos < 0 || pos > gt->num_tareas)
		return;

	list_for_each_entry_safe(t, tmp, &gt->tareas, head) {
		if (i == pos) {
			list_del(&t->head);
			tarea_free(t);
			break;
		}

		i++;
	}

	gt->num_tareas--;
	if (gt->num_tareas == 0)
		gt->flags &= ~(1 << GESTOR_TAREAS_TAREAS);
}

void gestor_tareas_set_tarea(struct gestor_tarea *gt, const void *data)
{
	struct tarea *t;
	//int pos;
	//int prioridad_t1, prioridad_t2;

	if (gt->num_tareas > GESTOR_TAREAS_MAXT) {
		printf("El gestor de tareas está lleno\n");
		return;
	}

	/*prioridad_t1 = *(int *)tarea_get_data((struct tarea *)data, T_PRIORIDAD);

	for (pos = 0; pos < gt->num_tareas; pos++) {
		prioridad_t2 = *(int *)tarea_get_data(gt->tareas[pos], T_PRIORIDAD);
		if (prioridad_t1 < prioridad_t2) break;
    	}*/
	t = (struct tarea *)data;
	list_add(&t->head, &gt->tareas);
	gt->num_tareas++;
	gt->flags |= (1 << GESTOR_TAREAS_NUM_TAREAS);
	gt->flags |= (1 << GESTOR_TAREAS_TAREAS);

}

const void *gestor_tareas_get_data(struct gestor_tarea *gt, uint16_t attr, uint32_t pos)
{
	int i = 0;
	struct tarea *t;

	if (!(gt->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case GESTOR_TAREAS_TAREAS:
		list_for_each_entry(t, &gt->tareas, head) {
			if (i == pos)
				break;
			i++;
		}

		return t;
	case GESTOR_TAREAS_NUM_TAREAS:
		return &gt->num_tareas;
	}
	return NULL;
}

uint32_t gestor_tareas_get_u32(struct gestor_tarea *gt, uint16_t attr)
{
	const void *ret = gestor_tareas_get_data(gt, attr, 0);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *gestor_tareas_get_str(struct gestor_tarea *gt, uint16_t attr)
{
	return gestor_tareas_get_data(gt, attr, 0);
}

struct tarea *gestor_tareas_get_tarea(struct gestor_tarea *gt, uint16_t attr, uint32_t pos)
{
	return (struct tarea *)gestor_tareas_get_data(gt, attr, pos);
}

int gestor_tareas_snprintf(char *buf, size_t size, struct gestor_tarea *gt)
{
	int ret = 0;
	struct tarea *t;

	ret = ret + snprintf(buf, size, "El gestor de tareas tiene %d tareas:\n",gt->num_tareas);

	list_for_each_entry(t, &gt->tareas, head) {
		ret = ret + tarea_snprintf(buf + ret, size - ret, t);
		ret = ret + snprintf(buf + ret, size - ret, "\n");
	}
	return ret;
}
