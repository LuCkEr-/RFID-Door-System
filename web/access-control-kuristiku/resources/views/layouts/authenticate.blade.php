@extends('layouts.app')

@section('wrapper')
<div class="container">
    <div class="row">
        <div class="col-md-4 col-md-offset-4">
            <div class="login-panel panel panel-default">
                <div class="panel-heading">
                    <h3 class="panel-title">@yield('authTitle')</h3>
                </div>
                @yield('authBody')
            </div>
        </div>
    </div>
</div>
@endsection