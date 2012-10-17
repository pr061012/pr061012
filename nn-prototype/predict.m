function predict(model, X)
    addpath('../nn/');

    action = nnPredict(model.t1, model.t2, X(1:2));

    if action == 1
        food_action = nnPredict(model.food_t1, model.food_t2, X(3:4));
        if food_action == 1
            printf("Going home to eat.\n");
        elseif food_action == 2
            printf("Eating food from inventory.\n");
        elseif food_action == 3
            printf("Searching for food.\n");
        end;
    elseif action == 2
        printf("Sleeping.\n");
    elseif action == 3
        printf("Doing nothing.\n");
    end;
end;
