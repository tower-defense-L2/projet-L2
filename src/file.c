#include "../include/file.h"

void file_init(file_T *file) {
  file->first = NULL;
  file->queue = NULL;
  file->length = 0;
}

void file_push(file_T *file, void *data) {
  element_T *element = malloc(sizeof(element_T));
  element->data = data;
  element->next = NULL;
  if (file_is_empty(file)) {
    file->first = element;
    file->queue = element;
  } else {
    file->queue->next = element;
    file->queue = element;
  }
  file->length++;
}

void *file_pop(file_T *file) {
  if (file_is_empty(file)) {
    return NULL;
  }
  element_T *element = file->first;
  file->first = element->next;
  file->length--;
  void *data = element->data;
  free(element);
  return data;
}

void *file_peek(file_T *file) {
  if (file_is_empty(file)) {
    return NULL;
  }
  return file->first->data;
}

int file_is_empty(file_T *file) {
  return file->first == NULL;
}

int file_is_end(file_T *file) {
  return file->queue == NULL;
}

void file_clear(file_T *file) {
  while (!file_is_empty(file)) {
    file_pop(file);
  }
}

int file_length(file_T *file) {
  return file->length;
}

void file_print(file_T *file, void (*print)(void *)) {
  printf("file[%d]{", file_length(file));
  element_T *tmp = file->first;
  while (tmp != NULL) {
    print(tmp->data);
    tmp = tmp->next;
    if (tmp != NULL) {
      printf(", ");
    }
  }
  printf("}");
}