#include <stdio.h>
#include <stdlib.h>

typedef struct _pizza pizza_t;
typedef double (* getCost)(struct _pizza * self);

typedef struct _pizza {
    getCost getCostFunc;
} pizza_t;

typedef struct _plainPizza {
    pizza_t base;
} plainPizza_t;

typedef struct _toppingDecorator {
    pizza_t base;
    pizza_t * decorate;
} toppingDecorator_t;

// these are the pizzas
double plainPizzaCost (plainPizza_t self) {
    return 5;
}

// these are the toppings
double mozzarellaCost (toppingDecorator_t * self) {
    return self->decorate->getCostFunc(self->decorate) + 3;
}
double tomatoCost (toppingDecorator_t * self) {
    return self->decorate->getCostFunc(self->decorate) + 2;
}
double peparoniCost (toppingDecorator_t * self) {
    return self->decorate->getCostFunc(self->decorate) + 1;
}

int main(int argc, const char * argv[]) {
    
    plainPizza_t plainPizza;
    plainPizza.base.getCostFunc = (getCost) plainPizzaCost;
    
    toppingDecorator_t mozzarella;
    mozzarella.base.getCostFunc = (getCost) mozzarellaCost;
    mozzarella.decorate = (pizza_t *) &plainPizza;
    
    toppingDecorator_t tomato;
    tomato.base.getCostFunc = (getCost) tomatoCost;
    tomato.decorate = (pizza_t *) &mozzarella;
    
    toppingDecorator_t salami;
    salami.base.getCostFunc = (getCost) peparoniCost;
    salami.decorate = (pizza_t *) &tomato;
    
    
    printf ("A plain pizza %f\n", plainPizza.base.getCostFunc((pizza_t *) &plainPizza));
    printf ("A salami pizza (incl. tomato and mozzarella) costs %f\n", salami.base.getCostFunc((pizza_t *) &salami));
}