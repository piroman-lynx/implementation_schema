
class cli<PipeModule {

  private:
    static cli instance* = 0;
    char *config_endl;

  public:

    PipeModule ( PipeModule* headPassParent );

    PipeModule<PipeModule ( void );

    virtual PipeModule getInstance(PipeModule* headPassParent);

    virtual PipeModule getInstance();

    virtual char* cin();

    virtual void cout(char* in);

}