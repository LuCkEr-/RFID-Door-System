@extends('layouts.app')

@section('content')
<div class="container">
    <div class="row">
        <div class="col-md-4 col-md-offset-4">
            <div class="login-panel panel panel-default">
                <div class="panel-heading">
                    <h3 class="panel-title">@yield('authTitle')</h3>
                </div>
                <div class="panel-body">
                    @yield('authBody')
                </div>
            </div>
        </div>
    </div>
</div>
@endsection