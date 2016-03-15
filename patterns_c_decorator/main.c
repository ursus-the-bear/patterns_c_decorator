#include <stdio.h>

typedef struct _toppingDecorator toppingDecorator_t;

typedef struct _pizza {
    double (* getCost) (toppingDecorator_t * self);
} pizza_t;

typedef struct _toppingDecorator {
    
    pizza_t tempPizza;
    pizza_t * delegate;
    
} toppingDecorator_t;

typedef struct _topping {
    
    toppingDecorator_t methods;
    pizza_t * delegate;
    
} topping_t;

typedef struct _order {
    
    pizza_t pizza;
    // something else? list of toppings?
    
} order_t;

// these are the pizzas
double plainPizzaCost (toppingDecorator_t * self) {
    return 5;
}

// these are the toppings
double mozzarellaCost (toppingDecorator_t * self) {
    return 3.0;
}
double tomatoCost (toppingDecorator_t * self) {
    return 1;
}

int main(int argc, const char * argv[]) {
    
    order_t myOrder;
    myOrder.pizza.getCost = &plainPizzaCost;
    printf ("My pizza costs %f\n", myOrder.pizza.getCost ((toppingDecorator_t *) &myOrder.pizza));
    
    toppingDecorator_t toppings;
    toppings.delegate = (pizza_t *) &myOrder;
    
    topping_t mozzarella;
    mozzarella.delegate = (pizza_t *) &myOrder;
    mozzarella.methods.delegate = (pizza_t *)&mozzarellaCost;
    printf ("My pizza costs %f\n", mozzarella.delegate->getCost ((toppingDecorator_t *) &mozzarella));
    
    
}