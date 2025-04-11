class BaseInstaller:
    """
    Base class for installers.
    """

    def install(self):
        """
        Install the distribution.
        """
        raise NotImplementedError("Install method not implemented.")
    
    def is_installed(self):
        """
        Check if the distribution is installed.
        """
        raise NotImplementedError("IsInstalled method not implemented.")
    
    def configure(self):
        """
        Configure the distribution.
        """
        raise NotImplementedError("Configure method not implemented.")
    
    def update(self):
        """
        Update the distribution.
        """
        raise NotImplementedError("Update method not implemented.")

    def uninstall(self):
        """
        Uninstall the distribution.
        """
        raise NotImplementedError("Uninstall method not implemented.")