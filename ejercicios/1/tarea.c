#include <string.h>
#include "tarea.h"

struct tarea *tarea_alloc(void)
{
	return (struct tarea *)malloc(sizeof(struct tarea));
}

void tarea_free(struct tarea *t)
{
	if (t->flags & (1 << NOMBRE_TAREA))
		xfree(t->nombre_tarea);

	if (t->flags & (1 << DESC_TAREA))
		xfree(t->desc_tarea);
	if (t->flags & (1 << NOMBRE_USUARIO_T))
		xfree(t->nombre_usuario_t);
	xfree(t);
}

bool tarea_is_set(const struct tarea *t, uint16_t attr)
{
	return t->flags & (1 << attr);
}

void tarea_unset(struct tarea *t, uint16_t attr)
{
	if (!(t->flags & (1 << attr)))
		return;

	switch (attr) {
	case NOMBRE_TAREA:
		if (t->nombre_tarea) {
			xfree(t->nombre_tarea);
			t->nombre_tarea = NULL;
		}
		break;
	case DESC_TAREA:
		if (t->desc_tarea) {
			xfree(t->desc_tarea);
			t->desc_tarea = NULL;
		}
		break;
	case TAREA_ID:
		break;
	case NOMBRE_USUARIO_T:
		if (t->nombre_usuario_t) {
			xfree(t->nombre_usuario_t);
			t->nombre_usuario_t = NULL;
		}
		break;
	case T_PRIORIDAD:
		break;
	}

	t->flags &= ~(1 << attr);
}

void tarea_set_data(struct tarea *t, uint16_t attr, const void *data,
			  uint32_t data_len)
{
	if (attr > __TAREAS_MAX)
		return;

	switch (attr) {
	case NOMBRE_TAREA:
		if (t->nombre_tarea)
			xfree(t->nombre_tarea);

		t->nombre_tarea = strdup(data);
		break;
	case DESC_TAREA:
		if (t->desc_tarea)
			xfree(t->desc_tarea);

		t->desc_tarea = strdup(data);
		break;
	case TAREA_ID:
		t->tarea_id = *((uint32_t *)data);
		break;
	case NOMBRE_USUARIO_T:
		if(t->nombre_usuario_t)
			xfree(t->nombre_usuario_t);
		t->nombre_usuario_t = strdup(data);
		break;
	case T_PRIORIDAD:
		t->t_prioridad = *((uint32_t *)data);
		break;
	}

	t->flags |= (1 << attr);
}

void tarea_set_u32(struct tarea *t, uint16_t attr, uint32_t data)
{
	tarea_set_data(t, attr, &data, sizeof(uint32_t));
}

void tarea_set_str(struct tarea *t, uint16_t attr, const char *data)
{
	tarea_set_data(t, attr, data, 0);
}

const void *tarea_get_data(struct tarea *t, uint16_t attr)
{
	if (!(t->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case NOMBRE_TAREA:
		return t->nombre_tarea;
	case DESC_TAREA:
		return t->desc_tarea;
	case TAREA_ID:
		return &t->tarea_id;
	case NOMBRE_USUARIO_T:
		return t->nombre_usuario_t;
	case T_PRIORIDAD:
		return &t->t_prioridad;
	}
	return NULL;
}

uint32_t tarea_get_u32(struct tarea *t, uint16_t attr)
{
	const void *ret = tarea_get_data(t, attr);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *tarea_get_str(struct tarea *t, uint16_t attr)
{
	return tarea_get_data(t, attr);
}

int tarea_snprintf(char *buf, size_t size, struct tarea *t)
{
	return snprintf(buf, size, "La tarea numero %d está enviada por %s."
	"Se llama %s y la descripción es %s y la prioridad es %d\n",
	t->tarea_id, t->nombre_usuario_t, t->nombre_tarea, t->desc_tarea, t->t_prioridad);
}
