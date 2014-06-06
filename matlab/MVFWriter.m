classdef MVFWriter<handle
    %
    %   Use the MVFWriter function with the write method to write MAIA video 
    %   data into a file from the MATLAB workspace.
    % 
    %   obj = MVFWriter (filename) constructs obj to create new MAIA video object.
    %   
    %   Examples of using class:
    %
    %       obj = MVFWriter ('filename.mvf');
    %       obj.width = 776;
    %       obj.height = 582;
    %       obj.bpp = 16;
    %       obj.bppUsed = 10;
    %       obj.channels = 1;
    %       obj.reserved = 0;
    %       obj.fps = 61;
    %       obj.numOfFrames = 0;
    %       open (obj);
    %       write (obj, frame);
    %       close (obj);
  
    
    properties (GetAccess = 'private', SetAccess = 'private')
        f
        filename
    end
    
    properties (GetAccess = 'public', SetAccess = 'public')
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
    
        function obj = MVFWriter (filename)
            % class constructor
            obj.filename = filename;
        end
        
        function obj = open (obj)
            obj.f = fopen (obj.filename, 'w');
            fseek (obj.f, 0, 'bof');
            writeHeader (obj);
        end
        
        function close (obj)
            fclose (obj.f);
        end
        
        function write (obj, frame)
            fseek (obj.f, 0, 'eof');
            fwrite (obj.f, frame, 'uint16');
            obj.numOfFrames = obj.numOfFrames + 1;
            writeHeader (obj);
        end
        
        function  writeHeader (obj)
            fseek (obj.f, 0, 'bof');
            fwrite (obj.f, obj.width, 'uint16');
            fwrite (obj.f, obj.height, 'uint16');
            fwrite (obj.f, obj.bpp, 'uint16');
            fwrite (obj.f, obj.bppUsed, 'uint16');
            fwrite (obj.f, obj.channels, 'uint16');
            fwrite (obj.f, obj.reserved, 'uint16');
            fwrite (obj.f, obj.fps , 'float');
            fwrite (obj.f, obj.numOfFrames, 'uint32');
        end
    end
    
end

