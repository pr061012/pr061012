function model = trainModel()
    addpath('../nn/');

    % Loading training datasets.
    X = load('main-nn-data')(:, 1 : end - 1);
    y = load('main-nn-data')(:, end);
    food_X = load('nn-1-data')(:, 1 : end - 1);
    food_y = load('nn-1-data')(:, end);

    % Training NNs.
    [t1 t2] = nnTrain(2, 3, 3, X, y, 0.1);
    [food_t1 food_t2] = nnTrain(2, 3, 3, food_X, food_y, 0.1);

    model.t1 = t1;
    model.t2 = t2;
    model.food_t1 = food_t1;
    model.food_t2 = food_t2;
end;
