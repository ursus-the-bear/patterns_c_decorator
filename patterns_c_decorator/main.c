//
//  main.c
//  klausur_c_delegation
//
//  Created by ursus on 14/03/16.
//  Copyright © 2016 Ursus Schneider. All rights reserved.
//

#include <stdio.h>

typedef struct _sound sound_t;
typedef struct _sound {
    void (* makeSound) ();
} sound_t;

typedef struct _animal animal_t;
typedef struct _animal {
    sound_t sound;
    void (* makeSound) (animal_t * self);
    void (* setSound) (animal_t * self, void * new_sound);
} animal_t;

void animalSetSound (animal_t * self, void * new_sound) {
    self->sound.makeSound = new_sound;
}

void animalMakeSound (animal_t * self) {
    self->sound.makeSound ();
}

void roar () {
    printf ("Roar\n");
}

void meow () {
    printf ("Meow\n");
}

int main(int argc, const char * argv[]) {
    
    animal_t cat;
    cat.setSound = &animalSetSound;
    cat.makeSound = &animalMakeSound;
    
    cat.setSound (&cat, &meow);
    cat.makeSound (&cat);
    
    cat.setSound (&cat, &roar);
    cat.makeSound (&cat);
    
}