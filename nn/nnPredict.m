function y = nnPredict(theta1, theta2, X)

    % Size of X.
    m = size(X, 1);

    % Calculating hypothesis.
    h1 = sigmoidFunction([ones(m, 1) X] * theta1');
    h2 = sigmoidFunction([ones(m, 1) h1] * theta2');

    % Getting the most possible value of y.
    [dummy, y] = max(h2, [], 2);
end
