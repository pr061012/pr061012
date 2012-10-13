function [theta1 theta2] = nnTrain(input_layer_size, ...
                                   hidden_layer_size, ...
                                   output_layer_size, ...
                                   X, y, lambda)

    % Initializing random theta matrices by values between -0.5 and 0.5.
    initial_theta1 = rand(hidden_layer_size, input_layer_size + 1) - 0.5;
    initial_theta2 = rand(output_layer_size, hidden_layer_size + 1) - 0.5;

    % Unrolling theta.
    initial_params = [initial_theta1(:); initial_theta2(:)];

    % Settings options for fminunc() function.
    options = optimset('MaxIter', 100);

    % Creating a short hand: costFunction will receive only one parameter (p --
    % theta unrolled matrices).
    costFunction = @(p) nnCostFunction(p, ...
                                       input_layer_size, ...
                                       hidden_layer_size, ...
                                       output_layer_size, ...
                                       X, y, lambda);

    % Running gradient descent.
    [params, cost] = fminunc(costFunction, initial_params, options);

    % Reshaping theta matrices.
    theta1 = reshape(params(1:hidden_layer_size * (input_layer_size + 1)), ...
                     hidden_layer_size, (input_layer_size + 1));
    theta2 = reshape(params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                     output_layer_size, (hidden_layer_size + 1));
end
