function [J grad] = nnCostFunction(params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   output_layer_size, ...
                                   X, y, lambda)

    % Actually we use Octave's gradient descent implementation (fminunc
    % function), that prefers theta to be a column vector instead of matrices.
    % Thus we need to reshape params vector to theta matrices.

    % From input layer to hidden.
    theta1 = reshape(params(1:hidden_layer_size * (input_layer_size + 1)), ...
                     hidden_layer_size, (input_layer_size + 1));

    % From hidden to output layer.
    theta2 = reshape(params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                     output_layer_size, (hidden_layer_size + 1));

    % Amount of examples.
    m = size(X, 1);

    % Converting vector y to binary matrix.
    Y = [];
    for i=1:output_layer_size
        Y = [Y (y == i)];
    end;

    % Adding bias units.
    X = [ones(m, 1) X];

    % Calculating hypothesis.
    % Hidden layer.
    z2 = X * theta1';
    a2 = [ones(m, 1) sigmoidFunction(z2)];

    % Output layer.
    z3 = a2 * theta2';
    a3 = sigmoidFunction(z3);

    % Out hypothesis.
    h = a3;

    % Calculating cost function without regularization term.
    log1 = log(h);
    log2 = log(1 - h);
    J = - sum( sum( log1 .* Y + log2 .* (1 - Y) ) ) / m;

    % Calculating regularization term.
    % We're ignoring first column in theta matrices because of bias units.
    reg1 = sum( sum( theta1(:, 2:end) .^ 2 ) );
    reg2 = sum( sum( theta2(:, 2:end) .^ 2 ) );

    % Adding regularization term.
    J += lambda * (reg1 + reg2) / (2 * m);

    % Calculating cost function gradient (backpropagation).
    delta3 = a3 - Y;
    delta2 = (delta3 * theta2(:, 2:end)) .* sigmoidFunctionGradient(z2);
    n1 = size(theta1, 1);
    n2 = size(theta2, 1);
    deriv1 = delta2' * X  + lambda * [zeros(n1, 1) theta1(:, 2:end)];
    deriv2 = delta3' * a2 + lambda * [zeros(n2, 1) theta2(:, 2:end)];

    % Finally, calculating gradient.
    theta1_grad = deriv1 / m;
    theta2_grad = deriv2 / m;

    % Unrolling gradient.
    grad = [theta1_grad(:); theta2_grad(:)];
end
