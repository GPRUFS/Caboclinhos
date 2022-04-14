function varargout = serial_teste(varargin)
% SERIAL_TESTE MATLAB code for serial_teste.fig
%      SERIAL_TESTE, by itself, creates a new SERIAL_TESTE or raises the existing
%      singleton*.
%
%      H = SERIAL_TESTE returns the handle to a new SERIAL_TESTE or the handle to
%      the existing singleton*.
%
%      SERIAL_TESTE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SERIAL_TESTE.M with the given input arguments.
%
%      SERIAL_TESTE('Property','Value',...) creates a new SERIAL_TESTE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before serial_teste_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to serial_teste_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help serial_teste

% Last Modified by GUIDE v2.5 21-Aug-2015 16:38:48

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @serial_teste_OpeningFcn, ...
                   'gui_OutputFcn',  @serial_teste_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before serial_teste is made visible.
function serial_teste_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to serial_teste (see VARARGIN)

% Choose default command line output for serial_teste
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes serial_teste wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = serial_teste_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global s

set(handles.pushbutton1,'UserData',0);
set(handles.pushbutton3,'UserData',0);
set(handles.pushbutton4,'UserData',0);
set(handles.pushbutton1,'enable','off')
set(handles.pushbutton2,'enable','on')
set(handles.popupmenu1,'value',1)
set(handles.popupmenu2,'value',1)
set(handles.popupmenu1,'enable','on')
set(handles.popupmenu2,'enable','on')
set(handles.edit4,'enable','on')
set(handles.edit5,'enable','on')
set(handles.edit9,'enable','off')
set(handles.edit10,'enable','off')
set(handles.edit11,'enable','off')
set(handles.edit12,'enable','off')
set(handles.pushbutton3,'enable','on')
set(handles.pushbutton4,'enable','on')

% Find a serial port object.
s = instrfind('Type', 'serial', 'Port', 'COM5', 'Tag', '');

% Create the serial port object if it does not exist
% otherwise use the object that was found.
if isempty(s)
    s = serial('COM5','BaudRate',9600,'DataBits',8);
else
    fclose(s);
    s = s(1);
end

% Connect to instrument object, obj1.
fopen(s);
% pause(0.05)
cont = 0;
z = 0; % define de 0, enviado quando o robô não esta selecionado
confirmacao = 255; % valor que informa a chegada de um pacote de dados
VR_max = 254; % 0 a 254;
logica = 0; % controla os bits de direção de rotação das rodas
vrD = 0; % define a magnitude de rotação da roda 1
vrE = 0; % define a magnitude de rotação da roda 2

while get(handles.pushbutton1,'UserData') == 0
    aux1 = get(handles.popupmenu1,'value');
    aux2 = get(handles.popupmenu2,'value');
    if (aux1 ~= 1 && get(handles.pushbutton3,'UserData'))% se algum robô estiver selecionado e a velocidade for enviada...
        set(handles.pushbutton3,'UserData',0);
        switch aux2
            case 1
                vrd_ = eval(get(handles.edit4,'string'));
                vre_ = eval(get(handles.edit5,'string'));
                
                % limita as velocidades das rodas
                if vrd_ > VR_max , vrd_ = VR_max; end
                if vrd_ < -VR_max , vrd_ = -VR_max; end
                if vre_ > VR_max , vre_ = VR_max; end
                if vre_ < -VR_max , vre_ = -VR_max; end
                vrD = round(abs(vrd_));
                vrE = round(abs(vre_));
                
                % atribuindo as direções à palavra logica
                logica = 0;
                if vrd_ > 0, logica = bitset(logica,4,'uint8'); end
                if vrd_ < 0, logica = bitset(logica,5,'uint8'); end
                if vre_ > 0, logica = bitset(logica,3,'uint8'); end
                if vre_ < 0, logica = bitset(logica,2,'uint8'); end
                
            case 2
                V = eval(get(handles.edit9,'string'));
                W = eval(get(handles.edit10,'string'));
                % zona morta
                zona_mortad = round(abs(eval(get(handles.edit11,'string'))));
                zona_mortae = round(abs(eval(get(handles.edit12,'string'))));
                if zona_mortad > VR_max , zona_mortad = VR_max; end
                if zona_mortae > VR_max , zona_mortae = VR_max; end
                
                % transformando V e W em vrD e vrE. limitadas a VR_max e aplicando a zona morta
                vrd_ = (V + W)*(VR_max-zona_mortad);
                vre_ = (V - W)*(VR_max-zona_mortae);
                
                % limita as velocidades das rodas
                if vrd_ > (VR_max-zona_mortad) , vrd_ = (VR_max-zona_mortad); end
                if vrd_ < -(VR_max-zona_mortad) , vrd_ = -(VR_max-zona_mortad); end
                if vre_ > (VR_max-zona_mortae) , vre_ = (VR_max-zona_mortae); end
                if vre_ < -(VR_max-zona_mortae) , vre_ = -(VR_max-zona_mortae); end
                                
                % adiciona a zona morta e arredonta para o inteiro
                if vrd_ >= 0
                    vrD = round(abs(vrd_ + zona_mortad));
                else
                    vrD = round(abs(vrd_ - zona_mortad));
                end
                if vre_ >= 0
                    vrE = round(abs(vre_ + zona_mortae));
                else
                    vrE = round(abs(vre_ - zona_mortae));
                end
                
                % atribuindo as direções à palavra logica
                logica = 0;
                if vrd_ > 0, logica = bitset(logica,4,'uint8'); end
                if vrd_ < 0, logica = bitset(logica,5,'uint8'); end
                if vre_ > 0, logica = bitset(logica,3,'uint8'); end
                if vre_ < 0, logica = bitset(logica,2,'uint8'); end
                
                set(handles.edit4,'String',num2str(vrD))
                set(handles.edit5,'String',num2str(vrE))
        end
    end
    
    %set(handles.edit4,'String',num2str(vrD))
    %set(handles.edit5,'String',num2str(vrE))
    
    % enviando o resultado dos comandos pela serial
    switch aux1
        case 2 % robô 0
            fwrite(s, evalin('base', num2str(confirmacao)), 'uint8');
            fwrite(s, evalin('base', num2str(logica)), 'uint8');
            fwrite(s, evalin('base', num2str(vrD)), 'uint8');
            fwrite(s, evalin('base', num2str(vrE)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
        case 3 % robô 1
            fwrite(s, evalin('base', num2str(confirmacao)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(logica)), 'uint8');
            fwrite(s, evalin('base', num2str(vrD)), 'uint8');
            fwrite(s, evalin('base', num2str(vrE)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
        case 4 % robô 2
            fwrite(s, evalin('base', num2str(confirmacao)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(logica)), 'uint8');
            fwrite(s, evalin('base', num2str(vrD)), 'uint8');
            fwrite(s, evalin('base', num2str(vrE)), 'uint8');
        otherwise % nenhum robô
            fwrite(s, evalin('base', num2str(confirmacao)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
            fwrite(s, evalin('base', num2str(z)), 'uint8');
    end
    
    if get(handles.pushbutton4,'UserData') == 1
            logica = 0;
            vrD = 0;
            vrE = 0;
            set(handles.pushbutton4,'UserData',0);
    end
        
    cont=cont+1;
    set(handles.edit1,'string',num2str(cont))
    drawnow
end

fwrite(s, evalin('base', num2str(confirmacao)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(confirmacao)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');
fwrite(s, evalin('base', num2str(z)), 'uint8');


% Disconnect from instrument object, obj1.
fclose(s);
% Clean up all objects.
delete(s);

set(handles.pushbutton1,'enable','on')
set(handles.pushbutton2,'enable','off')

set(handles.popupmenu1,'value',1)
set(handles.popupmenu2,'value',1)
set(handles.popupmenu1,'enable','off')
set(handles.popupmenu2,'enable','off')
set(handles.edit4,'enable','off')
set(handles.edit5,'enable','off')
set(handles.edit4,'String',0)
set(handles.edit5,'String',0)
set(handles.edit9,'String',0)
set(handles.edit10,'String',0)
set(handles.edit9,'enable','off')
set(handles.edit10,'enable','off')
set(handles.edit11,'enable','off')
set(handles.edit12,'enable','off')
set(handles.pushbutton3,'enable','off')
set(handles.pushbutton4,'enable','off')


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.pushbutton1,'UserData',1);



% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1


% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit4_Callback(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit4 as text
%        str2double(get(hObject,'String')) returns contents of edit4 as a double


% --- Executes during object creation, after setting all properties.
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit5_Callback(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit5 as text
%        str2double(get(hObject,'String')) returns contents of edit5 as a double


% --- Executes during object creation, after setting all properties.
function edit5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.pushbutton3,'UserData',1);


% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.pushbutton4,'UserData',1);



function edit6_Callback(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit6 as text
%        str2double(get(hObject,'String')) returns contents of edit6 as a double


% --- Executes during object creation, after setting all properties.
function edit6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu2.
function popupmenu2_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu2
aux = get(handles.popupmenu2,'value');
switch aux
    case 1
        set(handles.edit4,'enable','on')
        set(handles.edit5,'enable','on')
        set(handles.edit9,'enable','off')
        set(handles.edit10,'enable','off')
        set(handles.edit11,'enable','off')
        set(handles.edit12,'enable','off')
    case 2
        set(handles.edit4,'enable','off')
        set(handles.edit5,'enable','off')
        set(handles.edit9,'enable','on')
        set(handles.edit10,'enable','on')
        set(handles.edit11,'enable','on')
        set(handles.edit12,'enable','on')
end


% --- Executes during object creation, after setting all properties.
function popupmenu2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end





function edit10_Callback(hObject, eventdata, handles)
% hObject    handle to edit10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit10 as text
%        str2double(get(hObject,'String')) returns contents of edit10 as a double


% --- Executes during object creation, after setting all properties.
function edit10_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit9_Callback(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit9 as text
%        str2double(get(hObject,'String')) returns contents of edit9 as a double


% --- Executes during object creation, after setting all properties.
function edit9_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit11_Callback(hObject, eventdata, handles)
% hObject    handle to edit11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit11 as text
%        str2double(get(hObject,'String')) returns contents of edit11 as a double


% --- Executes during object creation, after setting all properties.
function edit11_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit12_Callback(hObject, eventdata, handles)
% hObject    handle to edit12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit12 as text
%        str2double(get(hObject,'String')) returns contents of edit12 as a double


% --- Executes during object creation, after setting all properties.
function edit12_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
