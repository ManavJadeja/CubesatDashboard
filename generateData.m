disp('Start')

%%% OPEN TEXT FILE
delete testData.txt
fid = fopen('testData.txt', 'a+');

%%% GENERATE AND WRITE DATA
tic
for x = 0:0.01:30
    y = sin(x);
    fprintf(fid, '%f %f\n', x, y);
    % disp([x,y])
    pause(0.01)
end
toc

%%% CLOSE TEXT FILE
fclose(fid);

disp('Done')