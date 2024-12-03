classdef PCA9685_servo < matlab.System ...
        & coder.ExternalDependency ...
        & matlabshared.sensors.simulink.internal.BlockSampleTime

    % Control the angle of the servo connected to the PCA9685 PWM board using i2c protocol
    %#codegen
    %#ok<*EMCA>

    properties
        boardAddress = uint8(64);
    end

    properties(Access = protected)
        Logo = 'IO Device Builder';
    end

    properties (Nontunable)
        pwmFrecuency = single(1200);
        servoChannel = uint8(0);
        servoMin = uint16(500);
        servoMax = uint16(2000);
    end

    properties (Access = private)


    end

    methods
        % Constructor
        function obj = PCA9685_servo(varargin)
            setProperties(obj,nargin,varargin{:});
        end
    end

    methods (Access=protected)
        function setupImpl(obj)
            if ~coder.target('MATLAB')
                coder.cinclude('PCA9685_servo.h');
                coder.ceval('setupFunctionPCA9685_servo', coder.ref(obj.boardAddress),1, (obj.pwmFrecuency),1, (obj.servoChannel),1, (obj.servoMin),1, (obj.servoMax),1);
            end
        end

        function validateInputsImpl(obj,varargin)
            %  Check the input size
            if nargin ~=0

                validateattributes(varargin{1},{'single'},{'2d','size',[1,1]},'','desireAngle');

            end
        end

        function currentAngle = stepImpl(obj ,desireAngle)
            currentAngle = single(zeros(1,1));

            if isempty(coder.target)
            else
                coder.ceval('stepFunctionPCA9685_servo',coder.ref(currentAngle),1, desireAngle,1, coder.ref(obj.boardAddress),1);
            end
        end

        function releaseImpl(obj)
            if isempty(coder.target)
            else

            end
        end
    end

    methods (Access=protected)
        %% Define output properties
        function num = getNumInputsImpl(~)
            num = 1;
        end

        function num = getNumOutputsImpl(~)
            num = 1;
        end

        function varargout = getInputNamesImpl(obj)
            varargout{1} = 'desireAngle';

        end

        function varargout = getOutputNamesImpl(obj)
            varargout{1} = 'currentAngle';
        end

        function flag = isOutputSizeLockedImpl(~,~)
            flag = true;
        end

        function varargout = isOutputFixedSizeImpl(~,~)
            varargout{1} = true;
        end

        function varargout = isOutputComplexImpl(~)
            varargout{1} = false;
        end

        function varargout = getOutputSizeImpl(~)
            varargout{1} = [1,1];
        end

        function varargout = getOutputDataTypeImpl(~)
            varargout{1} = 'single';
        end

        function maskDisplayCmds = getMaskDisplayImpl(obj)
            outport_label = [];
            num = getNumOutputsImpl(obj);
            if num > 0
                outputs = cell(1,num);
                [outputs{1:num}] = getOutputNamesImpl(obj);
                for i = 1:num
                    outport_label = [outport_label 'port_label(''output'',' num2str(i) ',''' outputs{i} ''');' ]; %#ok<AGROW>
                end
            end
            inport_label = [];
            num = getNumInputsImpl(obj);
            if num > 0
                inputs = cell(1,num);
                [inputs{1:num}] = getInputNamesImpl(obj);
                for i = 1:num
                    inport_label = [inport_label 'port_label(''input'',' num2str(i) ',''' inputs{i} ''');' ]; %#ok<AGROW>
                end
            end
            icon = 'PCA9685_servo';
            maskDisplayCmds = [ ...
                ['color(''white'');',...
                'plot([100,100,100,100]*1,[100,100,100,100]*1);',...
                'plot([100,100,100,100]*0,[100,100,100,100]*0);',...
                'color(''blue'');', ...
                ['text(38, 92, ','''',obj.Logo,'''',',''horizontalAlignment'', ''right'');',newline],...
                'color(''black'');'], ...
                ['text(52,50,' [''' ' icon ''',''horizontalAlignment'',''center'');' newline]]   ...
                inport_label ...
                outport_label
                ];
        end

        function sts = getSampleTimeImpl(obj)
            sts = getSampleTimeImpl@matlabshared.sensors.simulink.internal.BlockSampleTime(obj);
        end
    end

    methods (Static, Access=protected)
        function simMode = getSimulateUsingImpl(~)
            simMode = 'Interpreted execution';
        end

        function isVisible = showSimulateUsingImpl
            isVisible = false;
        end
    end

    methods (Static)
        function name = getDescriptiveName(~)
            name = 'PCA9685_servo';
        end

        function tf = isSupportedContext(~)
            tf = true;
        end

        function updateBuildInfo(buildInfo, context)
            coder.extrinsic('codertarget.targethardware.getTargetHardware');
            hCS = coder.const(getActiveConfigSet(bdroot));
            targetInfo = coder.const(codertarget.targethardware.getTargetHardware(hCS));

            % Added this env variable to fetch the comm libraries required only for Arduino target.
            % The env variable is cleared at the end of
            % "GenerateWrapperMakefile.m" file.
            if contains(targetInfo.TargetName,'arduinotarget')
                setenv('Arduino_ML_Codegen_I2C', 'Y');
            end

            buildInfo.addIncludePaths('C:\Users\esaro\MATLAB Drive\Robotica\E6R-1\2.Firmware\libraries\references\Adafruit-PWM-Servo-Driver-Library');
            buildInfo.addIncludePaths('C:\Users\esaro\MATLAB Drive\Robotica\E6R-1\2.Firmware\libraries\references\Adafruit_BusIO');

            buildInfo.addIncludePaths('C:\Users\esaro\MATLAB Drive\Robotica\E6R-1\2.Firmware\libraries');
            addSourceFiles(buildInfo,'Adafruit_PWMServoDriver.cpp','C:\Users\esaro\MATLAB Drive\Robotica\E6R-1\2.Firmware\libraries\references\Adafruit-PWM-Servo-Driver-Library');
            addSourceFiles(buildInfo,'Adafruit_BusIO_Register.cpp','C:\Users\esaro\MATLAB Drive\Robotica\E6R-1\2.Firmware\libraries\references\Adafruit_BusIO');
            addSourceFiles(buildInfo,'Adafruit_I2CDevice.cpp','C:\Users\esaro\MATLAB Drive\Robotica\E6R-1\2.Firmware\libraries\references\Adafruit_BusIO');
            addSourceFiles(buildInfo,'Adafruit_SPIDevice.cpp','C:\Users\esaro\MATLAB Drive\Robotica\E6R-1\2.Firmware\libraries\references\Adafruit_BusIO');
            addSourceFiles(buildInfo,'PCA9685_servo.cpp','C:\Users\esaro\MATLAB Drive\Robotica\E6R-1\2.Firmware\libraries');

        end
    end
end
