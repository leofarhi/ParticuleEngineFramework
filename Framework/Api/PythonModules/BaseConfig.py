import os
import json
import copy

class Var:
    def __init__(self, var_type, default_value=None, description=None, common=False):
        self.var_type = var_type
        self.default_value = default_value
        self.description = description
        self.value = default_value
        self.common = common

    def Clone(self):
        new_obj = self.__class__.__new__(self.__class__)
        new_obj.__dict__ = copy.deepcopy(self.__dict__)
        return new_obj

    def Load(self, value):
        raise NotImplementedError("Load method must be implemented in subclasses")
    
    def ToData(self):
        return self.value
    
    def ToConfig(self):
        return {
            "type": self.var_type,
            "description": self.description,
        }

class VarInt(Var):
    def __init__(self, default_value=0, *args, **kwargs):
        super().__init__("int", default_value, *args, **kwargs)

    def Load(self, value):
        self.value = self.default_value
        try:
            self.value = int(value)
        except ValueError:
            raise ValueError(f"Error: Invalid value for {self.description}. Expected an integer.")

class VarFloat(Var):
    def __init__(self, default_value=0, *args, **kwargs):
        super().__init__("float", default_value, *args, **kwargs)

    def Load(self, value):
        self.value = self.default_value
        try:
            self.value = float(value)
        except ValueError:
            raise ValueError(f"Error: Invalid value for {self.description}. Expected a float.")

class VarString(Var):
    def __init__(self, default_value="", *args, **kwargs):
        super().__init__("string", default_value, *args, **kwargs)

    def Load(self, value):
        self.value = str(value)

class VarBool(Var):
    def __init__(self, default_value=False, *args, **kwargs):
        super().__init__("bool", default_value, *args, **kwargs)

    def Load(self, value):
        self.value = self.default_value
        if isinstance(value, bool):
            self.value = value
        else:
            raise ValueError(f"Error: Invalid value for {self.description}. Expected a boolean.")

class VarList(Var):
    def __init__(self, type_instance, default_value=None, *args, **kwargs):
        if default_value is None:
            default_value = []
        super().__init__("list", default_value, *args, **kwargs)
        if not isinstance(type_instance, Var):
            raise ValueError("item_type_instance must be an instance of Var")
        self.type_instance = type_instance

    def Load(self, value):
        self.value = []
        if isinstance(value, list):
            for item in value:
                item_instance = self.type_instance.Clone()
                item_instance.Load(item)
                self.value.append(item_instance)
        else:
            raise ValueError(f"Error: Invalid value for {self.description}. Expected a list.")

    def ToData(self):
        return [item.ToData() for item in self.value]

    def ToConfig(self):
        config = super().ToConfig()
        config["template_type"] = self.type_instance.ToConfig()
        return config

class VarEnum(Var):
    def __init__(self, enum_values, default_value=None, *args, **kwargs):
        if default_value is None:
            default_value = enum_values[0] if enum_values else None
        super().__init__("enum", default_value, *args, **kwargs)
        self.enum_values = enum_values

    def Load(self, value):
        self.value = self.default_value
        if value in self.enum_values:
            self.value = value
        else:
            raise ValueError(f"Error: Invalid value for {self.description}. Expected one of {self.enum_values}.")

    def ToConfig(self):
        config = super().ToConfig()
        config["enum_values"] = self.enum_values
        return config
    
class VarPath(VarString):
    def __init__(self, default_value="", *args, **kwargs):
        super().__init__(default_value, *args, **kwargs)
        self.var_type = "path"

    def Load(self, value):
        self.value = self.default_value
        path = str(value)
        path = os.path.normpath(path)  # Normalize the path
        self.value = path
    
class VarDict(Var):
    def __init__(self, dict_of_instance, default_value=None, *args, **kwargs):
        if default_value is None:
            default_value = {}
        super().__init__("dict", default_value, *args, **kwargs)
        if not isinstance(dict_of_instance, dict):
            raise ValueError("dict_of_instance must be a dictionary")
        for key, value in dict_of_instance.items():
            if not isinstance(value, Var):
                raise ValueError(f"Value for key '{key}' must be an instance of Var")
        self.dict_of_instance = dict_of_instance

    def Load(self, value):
        self.value = self.default_value
        if isinstance(value, dict):
            for key, var in self.dict_of_instance.items():
                if key in value:
                    var = var.Clone()
                    var.Load(value[key])
                    self.value[key] = var
                else:
                    raise ValueError(f"Error: Missing key '{key}' in {self.description}.")
        else:
            raise ValueError(f"Error: Invalid value for {self.description}. Expected a dictionary.")

    def ToData(self):
        data = {}
        for key, var in self.value.items():
            data[key] = var.ToData()
        return data
    
    def ToConfig(self):
        config = super().ToConfig()
        config["template_type"] = {key: var.ToConfig() for key, var in self.dict_of_instance.items()}
        return config
    
class VarFreeDict(Var):
    def __init__(self, key_type, value_type, default_value=None, *args, **kwargs):
        if default_value is None:
            default_value = {}
        super().__init__("dict", default_value, *args, **kwargs)
        self.key_type = key_type
        self.value_type = value_type
        if not isinstance(key_type, Var) or not isinstance(value_type, Var):
            raise ValueError("key_type and value_type must be instances of Var")
    
    def Load(self, value):
        self.value = self.default_value
        if isinstance(value, dict):
            for key, val in value.items():
                key_instance = self.key_type.Clone()
                key_instance.Load(key)
                val_instance = self.value_type.Clone()
                val_instance.Load(val)
                self.value[key_instance.ToData()] = val_instance
        else:
            raise ValueError(f"Error: Invalid value for {self.description}. Expected a dictionary.")
        
    def ToData(self):
        data = {}
        for key, val in self.value.items():
            data[key] = val.ToData()
        return data
    
    def ToConfig(self):
        config = super().ToConfig()
        config["key_type"] = self.key_type.ToConfig()
        config["value_type"] = self.value_type.ToConfig()
        return config
    

class BaseConfig:
    def Load(self, dico):
        for name, var in self.__dict__.items():
            if isinstance(var, Var) and name in dico:
                var.Load(dico[name])
    def GetData(self, exclude_common=False):
        data = {}
        for name, var in self.__dict__.items():
            if isinstance(var, Var):
                if not exclude_common or not var.common:
                    data[name] = var.ToData()
        return data

    def GetConfig(self, exclude_common=False):
        config = {}
        for name, var in self.__dict__.items():
            if isinstance(var, Var):
                if not exclude_common or not var.common:
                    config[name] = var.ToConfig()
        return config
    
    def PrintData(self):
        data = self.GetData()
        print(json.dumps(data, indent=4))

    def PrintConfig(self):
        config = self.GetConfig()
        print(json.dumps(config, indent=4))

class BaseMakeConfig(BaseConfig):
    def __init__(self, distribution, is_library):
        super().__init__()
        self.cwd = os.getcwd()
        self.distribution = VarString(distribution, "Distribution name",common=False)
        self.is_library = VarBool(is_library, "Is this a library?",common=True)
        self.clean = VarBool(True, "Clean the build directory before building",common=True)
        self.debug = VarBool(False, "Enable debug mode",common=True)
        self.source_files = VarList(VarPath("","(*.c, *.cpp, *.h)"),[], "Source files to be compiled",common=True)
        self.include_paths = VarList(VarPath("","Path of directory"),[], "Include paths for the compiler",common=True)
        self.library_paths = VarList(VarPath("","Path of directory"),[], "Library paths for the linker",common=True)
        self.defines = VarFreeDict(VarString("","MACRO"),VarString("","value"),{}, "Preprocessor defines",common=True)
        self.output_file = VarString("output", "Output file name (without extension)",common=True)
        self.build_dir = VarPath("build", "Directory to store the build files",common=True)
        self.bin_dir = VarPath("bin", "Directory to store the final binary",common=True)
        self.project_name = VarString("MyApp", "Project name",common=True)
