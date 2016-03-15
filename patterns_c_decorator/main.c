#include <stdio.h>

typedef struct _pizza {
    double (* getCost) ();
} pizza_t;

typedef struct _toppingDecorator {
    double (* getCost) ();
    pizza_t tempPizza;
} toppingDecorator_t;

// these are the pizzas
double plainPizzaCost () {
    return 5;
}
double thickCrustPizzaCost () {
    return 7;
}

// these are the toppings
double mozzarellaCost (toppingDecorator_t * self) {
    return self->tempPizza.getCost () + 3.0;
}
double tomatoCost (toppingDecorator_t * self) {
    return self->tempPizza.getCost () + 1;
}

int main(int argc, const char * argv[]) {
    
    pizza_t plainPizza;
    plainPizza.getCost = &plainPizzaCost;
    
    pizza_t thickCrustPizza;
    thickCrustPizza.getCost = &thickCrustPizzaCost;
    
    toppingDecorator_t mozzarella;
    mozzarella.tempPizza = plainPizza;
    mozzarella.getCost = &mozzarellaCost;
    
    toppingDecorator_t tomato;
    tomato.tempPizza = mozzarella.tempPizza;
    tomato.getCost = &tomatoCost;
    
    // now print the cost
    printf ("A plain pizza costs %f\n", plainPizza.getCost ());
    printf ("A mozzarella pizza costs %f\n", mozzarella.getCost (&mozzarella));
    printf ("A tomato and mozzarella pizza costs %f\n", tomato.getCost (&mozzarella));
}