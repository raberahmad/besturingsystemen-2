/*
 *
 * BertOS - Memory allocator
 * src/alloc.c
 *
 * Copyright (C) 2019 Bastiaan Teeuwen <bastiaan@mkcl.nl>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 */

#include <alloc.h>

static struct block *head;

/* A pointer to the end of the kernel, all memory past this point is free */
extern uintptr_t kern_end;

static void *block_alloc(size_t n)
{
	struct block *bptr;
	

	if (head == NULL){
		head = &kern_end;
		bptr= head;
	}
	else{
		struct block *i;
		for(i=head; i->next!=NULL; i=i->next);
		bptr=i->addr+i->size;
	}

	bptr->addr= sizeof(struct block)+bptr;
	bptr->size=n;
	bptr->used=1;
	bptr->next=NULL;

	return bptr->addr;
	
	
}

static void block_free(struct block *bptr)
{
	bptr->used = false;
}

static void *block_get(size_t n)
{
	for(struct block *i = head; i->next!=NULL; i=i->next){
		if(i->used==0){
			if (n <= i->size){
				i->used=1;
				return i->addr;
			}
		}
	}

	return NULL;
}

void *malloc(size_t n)
{	
	if (n==0){
		return NULL;
	}
	void *tptr = block_get(n);

	if(tptr!=NULL){
		return tptr;
	}
	
	return block_alloc(n);		
}

void free(void *ptr)
{
	if(ptr !=NULL){
		block_free(ptr-sizeof(struct block));
	}
}

void *realloc(void *ptr, size_t n)
{
	/* TODO */
}

void *calloc(size_t n, size_t m)
{
	/* TODO */
}
