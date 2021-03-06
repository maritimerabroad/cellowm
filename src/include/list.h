#pragma once

struct window_list * new_empty_node(struct window_list ** list);
void bring_to_head(struct window_list ** list, struct window_list * node);

struct window_list * pop_node(struct window_list ** list, struct window_list * node);
void free_node(struct window_list ** list, struct window_list * node);
void free_list(struct window_list ** list);

