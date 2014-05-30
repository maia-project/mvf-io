classdef MVFReader
    %
    %   Use the MVFReader function with the read method to read MAIA video 
    %   data from a file into the MATLAB workspace.
    % 
    %   obj = MVFReader (filename) constructs obj to read MAIA video data from the file named filename.
    % 
    %   Examples of using read function:
    %
    %       video = read (obj, 1);          % first frame only
    %       video = read (obj, Inf);        % last frame only 
    %       video = read (obj, [1 10]);     % first 10 frames
    %       video = read (obj, [50 Inf]);   % frame 50 thru end
    
    properties (GetAccess = 'private', SetAccess = 'private')
        f
    end
    
    properties (GetAccess = 'public', SetAccess = 'private')
        width
        height
        bpp
        bppUsed
        channels
        reserved
        fps
        numOfFrames
    end
    
    methods
    
        function obj = MVFReader (filename)
            % class constructor
            if nargin == 1
                obj.f = fopen (filename);
                obj.width = fread (obj.f, 1, 'uint16');
                obj.height = fread (obj.f, 1, 'uint16');
                obj.bpp = fread (obj.f, 1, 'uint16');
                obj.bppUsed = fread (obj.f, 1, 'uint16');
                obj.channels = fread (obj.f, 1, 'uint16');
                obj.reserved = fread (obj.f, 1, 'uint16');
                obj.fps = fread (obj.f, 1, 'float');
                obj.numOfFrames = fread (obj.f, 1, 'uint32');
            else
            end
        end
        
        function frame = read (obj, num)
            if isscalar (num)
                if isinf(num) 
                    num = obj.numOfFrames;
                end
                if num > obj.numOfFrames
                    warning ('read:out', 'Requested index extends beyond the end of the file. Using last frame instead.');
                    num = obj.numOfFrames;
                end
                if num < 1
                    warning ('read:zero', 'Index should be positive integer. Using 1 instead.');
                end
                fseek (obj.f, 20 + 2*(num-1)*obj.width*obj.height, 'bof');
                frame = fread (obj.f, [obj.width obj.height], 'uint16');
            else
                if isinf(num) 
                    num = obj.numOfFrames;
                end
                if num(1) > num(2)
                    error ('read:bigger', 'Invalid range, lower limit extends upper limit');
                end
                if num(2) > obj.numOfFrames
                    warning ('read:out', 'Requested index extends beyond the end of the file. Using last frame instead.');
                    num = obj.numOfFrames;
                end
                if num(1) < 1
                    warning ('read:zero', 'Index should be positive integer. Using 1 instead.');
                end
                fseek (obj.f, 20 + 2*(num(1)-1)*obj.width*obj.height, 'bof');
                for a = num(1):num(2)
                    frame(:,:,a) = fread (obj.f, [obj.width obj.height], 'uint16');
                end
            end
        end
    end
    
end

