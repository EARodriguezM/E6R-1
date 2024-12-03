function ImportModel

%% Imports robot model into a Rigid Body Tree

    % Load the URDF file
    %
    eour6dof = importrobot("model/robot.urdf");
        
    % Configure the data format and show the robot in the home position
    robot4dof.DataFormat = 'row';

    %% Save the Rigid Body Tree to a file
    curDir = pwd;
    saveDir = fileparts(mfilename('fullpath'));
    cd(saveDir)
    save eour6dof eour6dof
    cd(curDir)

end