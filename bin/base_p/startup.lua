--
-- ��� ����������� �������� ��������: ����� ��������, �������� � �.�.
-- ����� ����� � ��������� �������� �� �����.
--
-- ����������� �������� �������� � ����� � ������ �����������
-- �������� UploadResourceGroup, ������� ���������� ����.
--
LoadResource("Resources.xml")

--
-- �������� ��������, ��������� � ��������� ������.
--
LoadEffects("Example2_Flames.xml")
LoadEffects("Example3_FindObject.xml")

--
-- �������� ����.
--
-- ���� ��������� ��� ����� (���������� ������������ ���� �������� � �.�.),
-- �� ������ Draw() � Update() �������� ���������� ������ �����, ����� ����
-- �������� �� �����. � ������ ���������� �� ����� � �������� ���� ���������� �����
-- AcceptMessage � ���������� "Init".
--
GUI:LoadLayers("Layers.xml")

--
-- ����������� �������� ������ ��������: ��������� ������� �������, �����������
-- ����������� � ����� � �.�. ��� ���������� ��������.
--
UploadResourceGroup("TestGroup")

--
-- ���� ������� �� �����.
--
-- � ���� ������ � �������� ���� ���� ��� ���������� ����� AcceptMessage("Init")
-- � �������� ���������� ������ Draw() � Update() � ������ �����.
--

Screen:pushLayer(GUI:getLayer("TestLayer"))

